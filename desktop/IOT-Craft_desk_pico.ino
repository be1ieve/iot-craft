
#define DEBUG_OUTPUT 1 // Debug output

#include <WiFi.h>
#include <BTstackLib.h>
#include <ArduinoJson.h>
#include <RPi_Pico_TimerInterrupt.h>

/*
 * Separate programs to different files and include them here.
 */
#include "struct.h" // define structs used in this program. must include prior to other files
#include "config.h" // almost everything need to change
//#include "display.h" // for generic epaper display functions
//#include "image.h" // support for display static images command
//#include "poker.h" // support for poker card command
#include "mqtt.h" // WiFi and MQTT functions
#include "ble_central.h" // BLE functions

// For pin interrupt
const int pin_count=ARRAY_SIZE(SENSOR_PINS);
bool sensor_triggered_flag = false;
int sensor_triggered_pin = 0;
const int sensor_trigger_interval = 3000; // time in ms
unsigned long last_sensor_triggered = 0;


/*
 * The MQTT protocol needs to ping the server periodicity or the server will think that client is offline.
 * So we need a timer to ping the MQTT server and also update subscribed topics.
 * But we can only do communication jobs in main thread not in event thread.
 * That makes the timer task can only raise a flag, then do the rest in main thread. 
 */
RPI_PICO_Timer timer1(1); // timer to update subscription status
bool mqttTimerFlag = false;
bool timer1Task(struct repeating_timer *t){
  mqttTimerFlag = true;
  return true;
}

void setup(){
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  /*
   * Set all defined sensor pins to internal pullup, that way we only need two pins: GPIO and GND.
   * Pins are bounded to the same interrupt function. Identify of which pin triggered is done there.
   */
  for(int i=0;i<pin_count;i++){
    pinMode(SENSOR_PINS[i].pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(SENSOR_PINS[i].pin), onSensorInterrupt, FALLING);
  }

  /*
   * Make sure DEVICE_NAME starts with NAME_PREFIX, otherwise replace it with WiFi mac address.
   */
  String nameString = DEVICE_NAME;
  if(!nameString.startsWith(NAME_PREFIX)){
    byte address[6];
    WiFi.macAddress(address);
    sprintf(DEVICE_NAME, "%s%02X%02X%02X\0",NAME_PREFIX , address[3], address[4], address[5]);
  }

#ifdef epd1in54_V2_H // This is the init part for 1.54inch
  epd.LDirInit();
  epd.Clear();
  drawEPDWelcome();
  epd.Sleep(); // go to sleep immediately to save power.
#endif

  connectMQTT(); // imply a connectWifi() as well

  timer1.attachInterruptInterval(MQTT_UPDATE_INTERVAL_US, timer1Task);

  BTstack.setBLEAdvertisementCallback(advertisementCallback);
  BTstack.setBLEDeviceConnectedCallback(deviceConnectedCallback);
  BTstack.setBLEDeviceDisconnectedCallback(deviceDisconnectedCallback);
  BTstack.setGATTServiceDiscoveredCallback(gattServiceDiscovered);
  BTstack.setGATTCharacteristicDiscoveredCallback(gattCharacteristicDiscovered);
  BTstack.setGATTCharacteristicReadCallback(gattReadCallback);
  //BTstack.setGATTCharacteristicSubscribedCallback(gattSubscribedCallback);
  //BTstack.setGATTCharacteristicNotificationCallback(gattCharacteristicNotification);
  BTstack.setGATTCharacteristicWrittenCallback(gattWrittenCallback);
  BTstack.setup(DEVICE_NAME);
  if(DEBUG_OUTPUT) Serial.println("Set BLE as central");

}

void loop() {
  if(mqttTimerFlag){ // time to update data from MQTT server
    mqttTimerFlag = false;
    connectMQTT(); // ping mqtt server and update subscription status
    if(DEBUG_OUTPUT) Serial.print(".");
  }
  if(!ble_connected_flag && handheldMqttInput[0] != '\0'){ // BLE disconnected
    mqttClient.unsubscribe(handheldMqttInput);
    handheldMqttInput[0] = '\0';
  }
  if(mqttToHandheldFlag){ // got MQTT message to handheld
    mqttToHandheldFlag = false;
    if(DEBUG_OUTPUT) Serial.printf("BLE send to handheld: %s\n", (char*)buffer);
    ble_connected_device.writeCharacteristic(&ble_rx_characteristic, buffer, buffer_length);
  }
  if(mqttToDeviceFlag){ // got MQTT message to device
    mqttToDeviceFlag = false;
    char tempStr[buffer_length+1];
    memcpy(tempStr, buffer, buffer_length);
    Serial.print("tempStr: ");
    Serial.println(tempStr);
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, tempStr);

#ifdef _POKER_H_ // add poker command
    if(doc.containsKey("poker")){
      if(DEBUG_OUTPUT) Serial.println("draw poker image");
      const char* poker = doc["poker"];
      drawPoker_154in_deg0(poker);
    }
    epd.DisplayPartFrame();
#endif
#ifdef _IMAGE_H_ // add image command
    if(doc.containsKey("image")){ // select which image to display
      const char* imageID = doc["image"];
      uint8_t x = 100;
      uint8_t y = 120;
      if(doc.containsKey("x") && doc.containsKey("y")){
        x = atoi(doc["x"]);
        y = atoi(doc["y"]);
      }
      if(DEBUG_OUTPUT) Serial.printf("Display image: %s at: %d,%d\n",imageID, x, y);
      drawImagePartial(imageID, x, y);
    }
    epd.DisplayPartFrame();
#endif
  }

  if(sensor_triggered_flag){ //GPIO triggered
    last_sensor_triggered = millis();
    sensor_triggered_flag = false;
    if(DEBUG_OUTPUT) Serial.printf("Sensed: %s\n", SENSOR_PINS[sensor_triggered_pin].name);
    scanBLE();
    if(!device_count) Serial.println("No IOT device found");
    else {
      if(DEBUG_OUTPUT) Serial.printf("Find %d IOT devices\n", device_count);
      int selected = 0;
      for(int i=0;i<device_count;i++){
        if(DEBUG_OUTPUT) Serial.printf("Addr: %s , RSSI: %d\n", nearby_devices[i].addr, nearby_devices[i].rssi);
        if(nearby_devices[i].rssi > nearby_devices[selected].rssi) selected = i;
      }
      BTstack.bleDisconnect(&ble_connected_device); // disconnect old connection
      Serial.printf("Connect to: %s\n", nearby_devices[selected].addr);
      connectBLE(nearby_devices[selected]);

      Serial.println("Data send to cloud:");
      Serial.printf("    Desktop name:    %s\n",DEVICE_NAME);
      Serial.printf("    Triggered pin:   %s\n",SENSOR_PINS[sensor_triggered_pin].name);
      Serial.printf("    Handheld name:   %s\n",handheld_name);
      Serial.printf("    battery level:   %s\n",handheld_battery_level);
      Serial.printf("    sensor value:    %s\n",handheld_value);

      StaticJsonDocument<256> doc; // use stack memory
      String jsonString;
      doc["name"] = DEVICE_NAME;
      doc["pin"] = SENSOR_PINS[sensor_triggered_pin].name;
      doc["handheld"] = handheld_name;
      doc["battery"] = handheld_battery_level;
      doc["value"] = handheld_value;
      serializeJson(doc,jsonString); // save as a string, ready to send out
      if(DEBUG_OUTPUT) Serial.println(jsonString);
      if(DEBUG_OUTPUT) Serial.println(jsonString.length());
      connectMQTT(); //ensure everything is OK
      char topicString[40];
      sprintf(topicString, "%s%s%s", MQTT_PREFIX, DEVICE_NAME, MQTT_TOPIC_OUTPUT); // send to server
      if(mqttClient.publish(topicString, jsonString.c_str()))
        Serial.println("publish message to MQTT broker");

      sprintf(handheldMqttInput, "%s%s%s", MQTT_PREFIX, handheld_name, MQTT_TOPIC_INPUT);
      if(DEBUG_OUTPUT) Serial.printf("Subscribe: %s\n", handheldMqttInput);
      mqttClient.subscribe(handheldMqttInput);
      Serial.printf("handheld device: %s is connected.", handheld_name);
    }
  }

  delay(100);
}

/*
 * There's no way to know which pin triggered, need to traverse the list
 */
void onSensorInterrupt(){
  if(sensor_triggered_flag | millis()-last_sensor_triggered < sensor_trigger_interval) return;
  for(int i=0;i<pin_count;i++){
    if(!digitalRead(SENSOR_PINS[i].pin)){
      sensor_triggered_flag = true;
      sensor_triggered_pin = i;
    }
  }
}

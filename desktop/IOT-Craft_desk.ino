
#define DEBUG_OUTPUT 1 // Debug output

#include <Arduino.h>
#include <WiFi.h>
#include <BTstackLib.h>
#include <ArduinoJson.h>
#include <RPi_Pico_TimerInterrupt.h>

/*
 * Separate programs to different files and include them here.
 */
#include "struct.h" // define structs used in this program. must include prior to other files
#include "config.h" // almost everything need to change
#include "mqtt.h" // WiFi and MQTT functions
#include "ble_central.h" // BLE functions
#include "display.h" // for generic epaper display functions
#include "image.h" // support for display static images command
#include "poker.h" // support for poker card command
#include "recommendation.h" // support recommendation map
#include "status.h" // handheld status image

// For pin interrupt
const int pin_count=ARRAY_SIZE(SENSOR_PINS);
volatile bool sensor_triggered_flag = false;
volatile int sensor_triggered_pin = 0;
const int sensor_trigger_interval = 5000; // time in ms
volatile unsigned long last_sensor_triggered = 0; // time in ms


/*
 * The MQTT protocol needs to ping the server periodicity or the server will think that client is offline.
 * So we need a timer to ping the MQTT server and also update subscribed topics.
 * But we can only do communication jobs in main thread not in event thread.
 * That makes the timer task can only raise a flag, then do the rest in main thread. 
 */
RPI_PICO_Timer timer1(1); // timer to update subscription status
volatile bool mqttTimerFlag = false;
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
    if(DEBUG_OUTPUT) sprintf(DEVICE_NAME, "%s%02X%02X%02X\0",NAME_PREFIX , address[3], address[4], address[5]);
  }

#ifdef epd1in54_V2_H // This is the init part for 1.54inch
  epd.LDirInit();
  epd.Clear();
  drawEPDBackground();  
  epd.SetFrameMemoryPartial(STANDBY_1Q,100,44, STANDBY_1Q_WIDTH,STANDBY_1Q_HEIGHT);
  epd.DisplayPartFrame();
#endif

  timer1.attachInterruptInterval(MQTT_UPDATE_INTERVAL_US, timer1Task);

  BTstack.setBLEAdvertisementCallback(advertisementCallback);
  BTstack.setBLEDeviceConnectedCallback(deviceConnectedCallback);
  BTstack.setBLEDeviceDisconnectedCallback(deviceDisconnectedCallback);
  BTstack.setGATTServiceDiscoveredCallback(gattServiceDiscovered);
  BTstack.setGATTCharacteristicDiscoveredCallback(gattCharacteristicDiscovered);
  BTstack.setGATTCharacteristicReadCallback(gattReadCallback);
  BTstack.setGATTCharacteristicWrittenCallback(gattWrittenCallback);
  BTstack.setup(DEVICE_NAME);
  if(DEBUG_OUTPUT) Serial.println("Set BLE as central");

#ifdef epd1in54_V2_H // This is the init part for 1.54inch
  epd.SetFrameMemoryPartial(STANDBY_2Q,100,44, STANDBY_2Q_WIDTH,STANDBY_2Q_HEIGHT);
  epd.DisplayPartFrame();
#endif

  connectWifi();

#ifdef epd1in54_V2_H // This is the init part for 1.54inch
  epd.SetFrameMemoryPartial(STANDBY_3Q,44,44, STANDBY_3Q_WIDTH,STANDBY_3Q_HEIGHT);
  epd.DisplayPartFrame();
#endif

  connectMQTT(); // imply a connectWifi() as well

#ifdef epd1in54_V2_H // This is the init part for 1.54inch
  epd.SetFrameMemoryPartial(STANDBY_4Q,44,44, STANDBY_4Q_WIDTH,STANDBY_4Q_HEIGHT);
  epd.DisplayPartFrame();
  epd.Sleep(); // go to sleep immediately to save power.
#endif

  rp2040.wdt_begin(8300); // enable watchdog to max 8.3 seconds
}

void loop() {
  rp2040.wdt_reset(); // feed the dog first!!

  if(mqttTimerFlag){ // time to update data from MQTT server
    mqttTimerFlag = false;
    connectMQTT(); // ping mqtt server and update subscription status
    if(DEBUG_OUTPUT) Serial.print(".");
  }
//  if(!ble_connected_flag && handheldMqttInput[0] != '\0'){ // BLE disconnected
//    mqttClient.unsubscribe(handheldMqttInput);
//    handheldMqttInput[0] = '\0';
//  }

  if(mqttToHandheldFlag){ // got MQTT message to handheld
    mqttToHandheldFlag = false;
    char mqtt_data[buffer_length+1];
    int mqtt_data_length = buffer_length;
    memcpy(mqtt_data, (const char*)buffer, buffer_length);
    mqtt_data[mqtt_data_length] = '\0';
    /*
     * Data sent from central is packaged into JSON format.
     */
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, buffer);
    if(DEBUG_OUTPUT){
      Serial.print("JSON: ");
      serializeJson(doc, Serial);
      Serial.println();
    }
    if(doc.containsKey("command") && doc["command"]=="occupy"){ // indicate that handheld device reconnected to one device
      const char* deviceID = doc["value"];
      if(strcmp(deviceID, DEVICE_NAME) != 0){
        Serial.println("Handheld device moved.");
        mqttClient.unsubscribe(handheldMqttInput);
        handheldMqttInput[0] = '\0';
      }
    }
    else{ // send message to handheld
      if(handheldMqttInput[0] == '\0') return;
      connectBLE(*linked_handheld_device);
      discoverBLEDevice();
      if(ble_connected_flag){
        if(DEBUG_OUTPUT){
          Serial.printf("BLE send to handheld: %s\n", (char*)mqtt_data);
          Serial.printf("ble_rx_characteristic: %d\n", ble_rx_characteristic);
        }
        ble_busy_flag = true;
        ble_connected_device.writeCharacteristic(&ble_rx_characteristic, (uint8_t*)mqtt_data, mqtt_data_length);
        while(ble_busy_flag) delay(100); // wait until ble_battery_service traversed
        rp2040.wdt_reset(); // feed the dog
        delay(5000); // wait for handheld to settle before disconnect
        rp2040.wdt_reset(); // feed the dog
        BTstack.bleDisconnect(&ble_connected_device); // Disconnect to force handheld device into broadcast mode.
     }
      else if(DEBUG_OUTPUT) Serial.println("No connection with previous handheld device.");
    }
  }
  if(mqttToDeviceFlag){ // got MQTT message to device
    mqttToDeviceFlag = false;
    /*
     * Data sent from central is packaged into JSON format.
     */
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, buffer);
    if(DEBUG_OUTPUT){
      Serial.print("JSON: ");
      serializeJson(doc, Serial);
      Serial.println();
    }
#ifdef _DISPLAY_H_
    epd.LDirInit();
    epd.Clear();
    rp2040.wdt_reset(); // feed the dog
    //drawEPDBackground(); // re-enable E-Paper
#endif
#ifdef _POKER_H_ // add poker command
    if(doc.containsKey("command") && doc["command"]=="poker"){
      if(DEBUG_OUTPUT) Serial.println("draw poker image");
      const char* poker = doc["value"];
      drawPoker_154in_deg0(poker);
    }
#endif
#ifdef _IMAGE_H_ // add image command
    if(doc.containsKey("command") && doc["command"]=="image"){ // select which image to display
      const char* imageID = doc["value"];
      uint8_t x = 100;
      uint8_t y = 120;
      if(doc.containsKey("x") && doc.containsKey("y")){
        x = atoi(doc["x"]);
        y = atoi(doc["y"]);
      }
      if(DEBUG_OUTPUT){
        Serial.print("Display image: ");
        Serial.print(imageID);
        Serial.print(" at: ");
        Serial.print(x);
        Serial.print(" , ");
        Serial.println(y);
      }
      drawImagePartial(imageID, x, y);
    }
#endif
#ifdef _RECOMMENDATION_H_
    if(doc.containsKey("command") && doc["command"]=="recommendation"){
      const char* recom = doc["value"];
      Serial.printf("Recommendation: %s\n", recom);
      drawRecommendation(recom);
    }
#endif
#ifdef _STATUS_H_
    if(doc.containsKey("command") && doc["command"]=="status"){
      const char* disp = doc["display"];
      const char* reason = doc["reason"];
      Serial.printf("Status: %s, %s\n", disp, reason);
      drawStatus(disp, reason);
    }
#endif

  }

  if(sensor_triggered_flag){ //GPIO triggered
    last_sensor_triggered = millis();
    if(DEBUG_OUTPUT) Serial.printf("Sensed: %s\n", SENSOR_PINS[sensor_triggered_pin].name);
    if(handheldMqttInput[0] != '\0'){ // unlink with previous connected device
      mqttClient.unsubscribe(handheldMqttInput);
      handheldMqttInput[0] = '\0';
    }
    scanBLE();
    if(!device_count) Serial.println("No IOT device found");
    else {
      if(DEBUG_OUTPUT) Serial.printf("Find %d IOT devices\n", device_count);
      int selected = 0;
      for(int i=0;i<device_count;i++){
        if(DEBUG_OUTPUT) Serial.printf("Addr: %s , RSSI: %d\n", nearby_devices[i].addr, nearby_devices[i].rssi);
        if(nearby_devices[i].rssi > nearby_devices[selected].rssi) selected = i;
      }
      Serial.printf("Connect to: %s\n", nearby_devices[selected].addr);
      connectBLE(nearby_devices[selected]); // connect to closest device
      linked_handheld_device = &nearby_devices[selected];
      discoverBLEDevice(); // gather informations needed
      Serial.println("Data send to cloud:");
      Serial.printf("    Desktop name:    %s\n",DEVICE_NAME);
      Serial.printf("    Triggered pin:   %s\n",SENSOR_PINS[sensor_triggered_pin].name);
      Serial.printf("    Handheld name:   %s\n",handheld_name);
/*
      Serial.printf("    battery level:   %s\n",handheld_battery_level);
      Serial.printf("    sensor value:    %s\n",handheld_value);
*/
      StaticJsonDocument<256> doc; // use stack memory
      String jsonString, jsonString2;
      doc["command"] = "connect_ble";
      doc["name"] = DEVICE_NAME;
      doc["pin"] = SENSOR_PINS[sensor_triggered_pin].name;
      doc["handheld"] = handheld_name;
/*
      doc["battery"] = handheld_battery_level;
      doc["value"] = handheld_value;
*/

      connectMQTT(); //ensure everything is OK
      char topicString[40];

      StaticJsonDocument<256> doc2; // use stack memory
      doc2["command"] = "occupy";
      doc2["value"] = DEVICE_NAME;
      serializeJson(doc2,jsonString2); // save as a string, ready to send out
      if(DEBUG_OUTPUT) Serial.println(jsonString2);
      if(DEBUG_OUTPUT) Serial.println(jsonString2.length());
      sprintf(topicString, "%s%s%s", MQTT_PREFIX, handheld_name, MQTT_TOPIC_INPUT); // send to other nodes listen to this handheld
      if(mqttClient.publish(topicString, jsonString2.c_str()))
        Serial.println("publish occupy message to MQTT broker");

      serializeJson(doc,jsonString); // save as a string, ready to send out
      if(DEBUG_OUTPUT) Serial.println(jsonString);
      if(DEBUG_OUTPUT) Serial.println(jsonString.length());
      sprintf(topicString, "%s%s%s", MQTT_PREFIX, DEVICE_NAME, MQTT_TOPIC_OUTPUT); // send to server
      if(mqttClient.publish(topicString, jsonString.c_str()))
        Serial.println("publish connect message to MQTT broker");

      sprintf(handheldMqttInput, "%s%s%s", MQTT_PREFIX, handheld_name, MQTT_TOPIC_INPUT);
      if(DEBUG_OUTPUT) Serial.printf("Subscribe: %s\n", handheldMqttInput);
      mqttClient.subscribe(handheldMqttInput);

      BTstack.bleDisconnect(&ble_connected_device); // Disconnect to force handheld device into broadcast mode.
    }

    sensor_triggered_flag = false;
  }

  delay(100);
}

/*
 * There's no way to know which pin triggered, need to traverse the list
 */
void onSensorInterrupt(){
  //if(sensor_triggered_flag | millis()-last_sensor_triggered < sensor_trigger_interval) return;
  if(sensor_triggered_flag) return;
  for(int i=0;i<pin_count;i++){
    if(!digitalRead(SENSOR_PINS[i].pin)){
      if(sensor_triggered_pin == i && millis()-last_sensor_triggered < sensor_trigger_interval) return;
      sensor_triggered_flag = true;
      sensor_triggered_pin = i;
    }
  }
}

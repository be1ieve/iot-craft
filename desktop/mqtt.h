#ifndef _MQTT_H_
#define _MQTT_H_

#include <PubSubClient.h>

#include "config.h" // need to get server settings

// For MQTT
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

/*
 * Desktop devices will subscribe to topic associated to its DEVICE_NAME and maintained all the time.
 * And it will also subscribe to the topic associated to handheld device when connected and unsubscribe when disconnected.
 * When we issue a message to a handheld device, it will send to connected desktop device and then pass to that handheld device directly. 
 */
char deviceMqttInput[40]; // topic for device input
char handheldMqttInput[40]; // topic for handheld input

bool mqttToDeviceFlag = false;
bool mqttToHandheldFlag = false;

/*
 * Everytime we update MQTT status, the server will tell us if any topic is updated.
 * When notified, we must extract DEVICE_NAME from topic string, then recognize its destination.
 * And the payload will be one single command wrapped in JSON format. Copy to global buffer for latter use in main thread.
 */
void mqttCallback(char* topic, byte* payload, unsigned int length){
  memcpy(buffer, payload,length);
  buffer_length = length;
  buffer[length] = '\0'; // always terminate string
  if(DEBUG_OUTPUT) Serial.printf("MQTT callback: %s : %s", topic, (char*)buffer);
  String topicString = String(topic);
  String targetNameString = topicString.substring(topicString.indexOf("/")+1,topicString.indexOf("/",topicString.indexOf("/")+1));
  if(handheld_name[0] != '\0' && targetNameString.equals(String(handheld_name))){
    if(DEBUG_OUTPUT) Serial.println("To Handheld");
    mqttToHandheldFlag = true;
  }
  else if(targetNameString.equals(String(DEVICE_NAME))){
    if(DEBUG_OUTPUT) Serial.println("To Device");
    mqttToDeviceFlag = true;
  }
}

void connectWifi(){
  if(WiFi.status() == WL_CONNECTED) return;
  if(DEBUG_OUTPUT) Serial.println("Wifi connecting");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // PICO W use block here, so we don't need to implement a waiting loop.
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Not connected to Wifi, restart device");
    delay(5000);
    rp2040.reboot();
  }
  Serial.println("WiFi ready");
}

void connectMQTT(){
  connectWifi(); // make sure wifi is connected
  if(mqttClient.connected()){
    mqttClient.loop(); // Will raise callback function if any topic is updated
    return;
  }
  if(DEBUG_OUTPUT) Serial.println("Connecting to MQTT");
  mqttClient.setServer(MQTT_SERVER, 1883);
  mqttClient.setCallback(mqttCallback);
  while (!mqttClient.connected()) {
    if(mqttClient.connect(DEVICE_NAME)){
      if(DEBUG_OUTPUT) Serial.println("MQTT connected");
        sprintf(deviceMqttInput, "%s%s%s", MQTT_PREFIX, DEVICE_NAME, MQTT_TOPIC_INPUT);
        mqttClient.subscribe(deviceMqttInput);
        if(DEBUG_OUTPUT) Serial.printf("Subscribe: %s\n", deviceMqttInput);
        if(handheldMqttInput[0] != '\0'){
          mqttClient.subscribe(handheldMqttInput);
          if(DEBUG_OUTPUT) Serial.printf("Subscribe: %s\n", handheldMqttInput);
        }
    }
    else{ // connect failed
      Serial.printf("Connect to MQTT failed: %d\n", mqttClient.state());
      delay(5000); // wait and retry
    }
  }

}

#endif

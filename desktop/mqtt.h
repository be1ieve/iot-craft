#ifndef _MQTT_H_
#define _MQTT_H_

#include <PubSubClient.h>

#include "config.h" // need to get server settings

// For MQTT
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

char deviceMqttInput[40]; // topic for device input
char handheldMqttInput[40]; // topic for handheld input

bool mqttToDeviceFlag = false;
bool mqttToHandheldFlag = false;


void mqttCallback(char* topic, byte* payload, unsigned int length){
  memcpy(buffer, payload,length);
  buffer_length = length;
  buffer[length] = '\0';
  if(DEBUG_OUTPUT) Serial.printf("MQTT callback: %s : %s", topic, (char*)buffer);
  String topicString = String(topic);
  String targetNameString = topicString.substring(topicString.indexOf("/")+1,topicString.indexOf("/",topicString.indexOf("/")+1));
  if(handheld_name[0] != '\0' && targetNameString.equals(String(handheld_name))){
    Serial.println("To Handheld");
    mqttToHandheldFlag = true;
  }
  else if(targetNameString.equals(String(DEVICE_NAME))){
    Serial.println("To Device");
    mqttToDeviceFlag = true;
  }
}

void connectWifi(){
  if(WiFi.status() == WL_CONNECTED) return;
  if(DEBUG_OUTPUT) Serial.println("Wifi connecting");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // PICO W use blocking mode
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Not connected to Wifi, restart device");
    delay(2000);
    rp2040.reboot();
  }
  Serial.println("WiFi ready");
}

void connectMQTT(){
  connectWifi(); // make sure wifi is connected
  if(mqttClient.connected()){ 
    mqttClient.loop();
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
    }
    else{ // connect failed
      if(DEBUG_OUTPUT) Serial.printf("Connect to MQTT failed: %d\n", mqttClient.state());
    }
  }

}

#endif

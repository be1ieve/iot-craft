

#define DEBUG_OUTPUT 1 // Debug output

#include <WiFi.h>
#include <ArduinoJson.h>
#include <RPi_Pico_TimerInterrupt.h>

/*
 * Separate programs to different files and include them here.
 */
#include "struct.h" // define structs used in this program. must include prior to other files
#include "config.h" // almost everything need to change
#include "mqtt.h" // WiFi and MQTT functions
#include "display.h" // for generic epaper display functions
#include "status.h" // handheld status image
#include "image.h" // support for display static images command
#include "poker.h" // support for poker card command
#include "recommendation.h" // support recommendation map

/*
 * Original library from: https://github.com/miguelbalboa/rfid
 * 1. Remove official MFRC522Extend library which is not RP2040 compatible.
 * 2. Move from SPI0 to SPI1, leave SPI0 for epaper module.
 *    Default SPI1 pins: MISO@GP8, MOSI@GP11, SCK@GP10
 *    In MFRC522.cpp, all SPI.xxx functions are replaced to SPI1.xxx
 */
#include <SPI.h>
#include "MFRC522.h"

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

const int RFID_COUNTS = ARRAY_SIZE(RFID_SENSORS);
MFRC522 mfrc522[RFID_COUNTS];   // Create MFRC522 instance.

/**
 * Initialize RFID and MQTT functions on core 0.
 * Leave core 1 for epaper module.
 */
void setup() {
  Serial.begin(9600); // Initialize serial communications with the PC
  pinMode(LED_BUILTIN, OUTPUT);

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

  timer1.attachInterruptInterval(MQTT_UPDATE_INTERVAL_US, timer1Task); // Create mqtt update timer

  // Init SPI1 bus. Since default pins are not set, need to set pins first.
  SPI1.setSCK(SPI1_SCK_PIN);
  SPI1.setRX(SPI1_RX_PIN);
  SPI1.setTX(SPI1_TX_PIN);
  SPI1.begin();
  for (uint8_t reader = 0; reader < RFID_COUNTS; reader++) {
    mfrc522[reader].PCD_Init(RFID_SENSORS[reader].ss_pin, RFID_SENSORS[reader].rst_pin); // Init each MFRC522 card
    if(DEBUG_OUTPUT){
      Serial.print(RFID_SENSORS[reader].name);
      Serial.print(F(": "));
      mfrc522[reader].PCD_DumpVersionToSerial();
    }
  }

#ifdef epd1in54_V2_H
  epd.SetFrameMemoryPartial(STANDBY_2Q,100,44, STANDBY_2Q_WIDTH,STANDBY_2Q_HEIGHT);
  epd.DisplayPartFrame();
#endif

  connectWifi();

#ifdef epd1in54_V2_H
  epd.SetFrameMemoryPartial(STANDBY_3Q,44,44, STANDBY_3Q_WIDTH,STANDBY_3Q_HEIGHT);
  epd.DisplayPartFrame();
#endif

  connectMQTT(); // imply a connectWifi() as well

#ifdef epd1in54_V2_H
  epd.SetFrameMemoryPartial(STANDBY_4Q,44,44, STANDBY_4Q_WIDTH,STANDBY_4Q_HEIGHT);
  epd.DisplayPartFrame();
//  epd.Sleep(); // go to sleep immediately to save power.
#endif

  rp2040.wdt_begin(8300); // enable watchdog to max 8.3 seconds

}

/**
 * Main loop for core 0.
 */
void loop() {
  rp2040.wdt_reset(); // feed the dog first!!

  if(mqttTimerFlag){ // time to update data from MQTT server
    mqttTimerFlag = false;
    connectMQTT(); // ping mqtt server and update subscription status
    if(DEBUG_OUTPUT) Serial.print(".");
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
    drawEPDBackground(); // re-enable E-Paper
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

  /*
   * RFID tag search 
   */
  for (uint8_t reader = 0; reader < RFID_COUNTS; reader++) {
    // Look for new cards

    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {
      String tag_name = RFID_SENSORS[reader].name;
      byte tag_uid[7] = {}; // rfid uid length is 4 or 7 bytes
      char tag_uid_hex[15] = {};
      int tag_uid_length = mfrc522[reader].uid.size;
      memcpy(tag_uid, mfrc522[reader].uid.uidByte, tag_uid_length); // shallow copy of uid
      if(tag_uid_length == 4)
        sprintf(tag_uid_hex, "%02X%02X%02X%02X",tag_uid[0],tag_uid[1],tag_uid[2],tag_uid[3]);
      else
        sprintf(tag_uid_hex, "%02X%02X%02X%02X%02X%02X%02X",tag_uid[0],tag_uid[1],tag_uid[2],tag_uid[3],tag_uid[4],tag_uid[5],tag_uid[6]);
      // Halt PICC
      mfrc522[reader].PICC_HaltA();
      // Stop encryption on PCD
      mfrc522[reader].PCD_StopCrypto1();

      if(DEBUG_OUTPUT){
        Serial.print(RFID_SENSORS[reader].name);
        // Show some details of the PICC (that is: the tag/card)
        Serial.print(F(": Card UID:"));
        Serial.println(tag_uid_hex);
      }

#ifdef _MQTT_H_
      StaticJsonDocument<256> doc; // use stack memory
      String jsonString;
      doc["command"] = "connect_rfid";
      doc["name"] = DEVICE_NAME;
      doc["pin"] = RFID_SENSORS[reader].name;
      doc["tag"] = tag_uid_hex;
      serializeJson(doc,jsonString); // save as a string, ready to send out
      if(DEBUG_OUTPUT) {
        Serial.print(jsonString.length());
        Serial.println(jsonString);
      }
      connectMQTT(); //ensure everything is OK
      char topicString[40];
      sprintf(topicString, "%s%s%s", MQTT_PREFIX, DEVICE_NAME, MQTT_TOPIC_OUTPUT); // send to server
      if(mqttClient.publish(topicString, jsonString.c_str()))
        Serial.println("publish message to MQTT broker");

#endif

    } //if (mfrc522[reader].PICC_IsNewC
  } //for(uint8_t reader
}

/*
 * Initialize Epaper on core 0.
 */
void setup1(){

}

/*
 * Main loop on core 0.
 */
void loop1(){
  
}

/**
 * Helper routine to dump a byte array as hex values to Serial.
 */
void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

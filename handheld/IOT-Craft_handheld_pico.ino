
#define DEBUG_OUTPUT 1 // Debug output

#include <BTstackLib.h>
#include <ArduinoJson.h>
#include <WiFi.h> // Only used for get mac address when DEVICE_NAME not starts with NAME_PREFIX.

/*
 * Separate programs to different files and include them here.
 */
#include "struct.h" // define structs used in this program. must include prior to other files
#include "config.h" // almost everything need to change
#include "display.h" // for generic epaper display functions
#include "image.h" // support for display static images command
#include "poker.h" // support for poker card command
#include "ble.h" // BLE functions

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  /*
   * Make sure DEVICE_NAME starts with NAME_PREFIX, otherwise replace it with WiFi mac address.
   */
  String nameString = DEVICE_NAME;
  if(!nameString.startsWith(NAME_PREFIX)){ // Force rewrite DEVICE_NAME
    byte address[6];
    WiFi.macAddress(address);
    sprintf(DEVICE_NAME, "%s%02X%02X%02X\0",NAME_PREFIX , address[3], address[4], address[5]); // reset DEVICE_NAME
  }

#ifdef epd1in54_V2_H // This is the init part for 1.54inch
  epd.LDirInit();
  epd.Clear();
  drawEPDWelcome(); // Display welcome page prior to BLE initialize
  epd.Sleep(); // go to sleep immediately to save power.
#endif

  // set BLE callbacks
  BTstack.setBLEDeviceConnectedCallback(deviceConnectedCallback);
  BTstack.setBLEDeviceDisconnectedCallback(deviceDisconnectedCallback);
  BTstack.setGATTCharacteristicRead(gattReadCallback);
  BTstack.setGATTCharacteristicWrite(gattWriteCallback);

  // set GATT Database
  // Needs to do it in sequence: add a service, then add all characteristics under it, then add another service, ...
  BTstack.addGATTService(new UUID(NAME_UUID));
  name_handle = BTstack.addGATTCharacteristic(new UUID(NAME_CHAR_UUID), ATT_PROPERTY_READ, DEVICE_NAME);
  BTstack.addGATTService(new UUID(BATTERY_UUID));
  batt_handle = BTstack.addGATTCharacteristicDynamic(new UUID(BATTERY_LEVEL_UUID), ATT_PROPERTY_READ | ATT_PROPERTY_NOTIFY, 0);
  BTstack.addGATTService(new UUID(UART_UUID));
  tx_handle = BTstack.addGATTCharacteristicDynamic(new UUID(UART_TX_UUID), ATT_PROPERTY_READ | ATT_PROPERTY_NOTIFY, 0);
  rx_handle = BTstack.addGATTCharacteristicDynamic(new UUID(UART_RX_UUID), ATT_PROPERTY_WRITE, 0);

  BTstack.setup(DEVICE_NAME);
  BTstack.startAdvertising();

}

void loop() {
  /*
   * When receiving, max data length is 20 bits. If more than 20 bits data is comming, it will be seperated to 18 bits per packet.
   * Since there's no way knowing when the receiving is finished, use a small delay to detect if no more data is sent.
   * Also, the max packet length is 600 bytes due to max MTU setting.
   * This means we can only fit a 32*32 b/w image in base64 format.
   * To overcome this we might need to implement another layer of potocol...
  */
  if(rx_receiving_flag){
    //drawEPDBackground(); // re-enable EPaper
    int rx_temp = rx_size;
    delay(100);
    while(rx_temp != rx_size){ // checks if data size changed.
      rx_temp = rx_size;
      delay(100);
    }
    /*
     * Data sent from central is packaged into JSON format.
     */
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, rx_buffer);
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
    epd.DisplayPartFrame();
#endif
    rx_size = 0;
    rx_receiving_flag = false; // indicate buffer can be cleared
  }
  delay(10);
}

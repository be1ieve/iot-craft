#ifndef _BLE_H_
#define _BLE_H_

#include "display.h" // Used for epaper display control

/*
 * When connected, light LED to indicate and re-enable epaper display.
 */
void deviceConnectedCallback(BLEStatus status, BLEDevice *device) {
  switch (status) {
    case BLE_STATUS_OK:
      Serial.println("Device connected!");
      digitalWrite(LED_BUILTIN, HIGH);
#ifdef epd1in54_V2_H // This is the init part for 1.54inch
      epd.LDirInit();
      drawEPDBackground(); // in order to clear old image, a full background redraw is required.
#endif
      break;
  }
}

void deviceDisconnectedCallback(BLEDevice * device) {
  Serial.println("Device disconnected.");
  digitalWrite(LED_BUILTIN, LOW);
#ifdef epd1in54_V2_H // This is the init part for 1.54inch
  epd.WaitUntilIdle();
  epd.Sleep();
#endif
  BTstack.startAdvertising();
}

/*
 * According to BTstack document, This function will be called twice.
 * First with buffer=null, we need to report the buffer size required.
 * Second with the actual value inside buffer
 */
uint16_t gattReadCallback(uint16_t value_handle, uint8_t * buffer, uint16_t buffer_size) {
  if(value_handle == tx_handle){
    if(buffer){
      int value = random(1000, 2000);
      if(DEBUG_OUTPUT) Serial.printf("GATT Read Callback: %d\n", value);
      sprintf((char*)buffer,"%4d\0",value);
    }
    return 4; // return the size needed
  }
  else if(value_handle == batt_handle){
    if(buffer){
      int value = random(1, 99);
      if(DEBUG_OUTPUT) Serial.printf("GATT BATT Callback: %d\n", value);
      sprintf((char*)buffer,"%02d\0",value);
    }
    return 3; // return the size needed
  }
  return 1;
}

/*
 * Strange behavior: When disconnect, called once with buffer=NULL
 */
int gattWriteCallback(uint16_t value_handle, uint8_t *buffer, uint16_t size) {
  if(DEBUG_OUTPUT) Serial.println("GATT Write callback");
  if(size)
    if(DEBUG_OUTPUT) Serial.println((const char*)buffer);  
  if(value_handle == rx_handle){
    rx_receiving_flag = true; // notify main loop into receiving loop
    if(rx_size+size < BUFFER_SIZE){
      strncpy(&rx_buffer[rx_size], (const char*)buffer, size);
      rx_size += size;
      rx_buffer[rx_size] = '\0'; // force close string
      if(DEBUG_OUTPUT) Serial.printf("RX: %s\n", rx_buffer);
    }
    else{
      if(DEBUG_OUTPUT) Serial.println("RX buffer full"); // althrough this shouldn't happen
    }
  }
  else if(DEBUG_OUTPUT) Serial.printf("Unknown handle destination: %d\n", value_handle);
  return size;
}

#endif

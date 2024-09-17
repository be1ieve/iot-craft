#ifndef _BLE_CENTRAL_H_
#define _BLE_CENTRAL_H_

//#include "display.h" // Used for epaper display control

/*
 * Global variables for BLE connection to access.
 * BTStack uses asynchronous callbacks, that means there's no program flow can be followed.
 * So we need to keep track of everything using global variables.
 */
BLEDevice ble_connected_device;
BLEService ble_battery_service;
BLEService ble_uart_service;
BLEService ble_name_service;
BLECharacteristic  ble_battery_characteristic;
BLECharacteristic  ble_tx_characteristic;
BLECharacteristic  ble_rx_characteristic;
BLECharacteristic  ble_name_characteristic;




/*
 * This is a passive BLE scan, which only wait for peripherials sending their advertisement data.
 * The time period must be larger than 2 * device advertisement time interval in order not to miss it.
 * By setting BTstack.setBLEAdvertisementCallback(advertisementCallback),
 * advertisementCallback() will be called whenever any BLE device found, multiple times.
 */
void scanBLE(){
  device_count = 0;
  Serial.println("Scanning nearby BLE device...");
  BTstack.bleStartScanning();
  delay(1000); // only scan for a short period
  BTstack.bleStopScanning();
  rp2040.wdt_reset(); // feed the dog!!

}

bool connectBLE(ble_adv_t device){
  /*
   * Althrough BTStack API provide a way to use formatted address string, but it didn't work.
   * The working solution is to parse the address from device.addr into six hex bytes then send to BTStack API.
   */
  uint8_t address[6];
  int parsed = sscanf(device.addr, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", address, address + 1,address + 2, address + 3, address + 4, address + 5);
  if(parsed == 6){
    ble_busy_flag = true;
    rp2040.wdt_reset(); // feed the dog!!
    BTstack.bleConnect(device.addr_type, address, 8000);
    rp2040.wdt_reset(); // feed the dog!!
    while(ble_busy_flag) delay(100); // wait until all service discovered
    if(ble_connected_flag) return true;
  }
  return false;
}

/*
 * Before calling this function, call connectBLE(*device) to establish connection with handheld device
 * This function do the following in sequence:
 * 1. Discover all services, looking for name, battery, and uart service.
 * 2. For each service, search for the required characteristic.
 * 3. Read name and battery level from name_characteristic and battery_characteristic.
 * 4. Save the uart_rx and uart_tx characteristics for futher use.
*/
bool discoverBLEDevice(){
  if(!ble_connected_flag) return false;
  ble_busy_flag = true;
  ble_connected_device.discoverGATTServices();
  while(ble_busy_flag) delay(100); // wait until ble_gatt_service traversed
  ble_busy_flag = true;
  ble_connected_device.discoverCharacteristicsForService(&ble_name_service);
  while(ble_busy_flag) delay(100); // wait until ble_name_service traversed
/*
  ble_busy_flag = true;
  ble_connected_device.discoverCharacteristicsForService(&ble_battery_service);
  while(ble_busy_flag) delay(100); // wait until ble_battery_service traversed
*/
  ble_busy_flag = true;
  ble_connected_device.discoverCharacteristicsForService(&ble_uart_service);
  while(ble_busy_flag) delay(100); // wait until ble_uart_service traversed

  if(DEBUG_OUTPUT) Serial.println("Reading handheld name");
  ble_busy_flag=true;
  ble_connected_device.readCharacteristic(&ble_name_characteristic);
  while(ble_busy_flag) delay(100);
  memcpy(handheld_name, (const char*)buffer, buffer_length);
  buffer_length = 0; // mark as used
/*
  if(DEBUG_OUTPUT) Serial.println("Reading handheld battery level");
  ble_busy_flag=true;
  ble_connected_device.readCharacteristic(&ble_battery_characteristic);    
  while(ble_busy_flag) delay(100);
  memcpy(handheld_battery_level, (const char*)buffer, buffer_length);
  buffer_length = 0; // mark as used
    
  if(DEBUG_OUTPUT) Serial.println("Reading handheld initial value");
  ble_busy_flag=true;
  ble_connected_device.readCharacteristic(&ble_tx_characteristic);    
  while(ble_busy_flag) delay(100);
  memcpy(handheld_value, (const char*)buffer, buffer_length);
  buffer_length = 0; // mark as used
*/
  return true;
}

/*
 * Called each time an advertisment received. Will also receive unrelated devices and redundant advertisements.
 * To distingish our handheld devices, all handheld device must have the same naming prefix: NAME_PREFIX defined in config.h
 * Also, signals too weak is ignored as well. A RSSI with -60dbm means devices farther than 1 meter.
 */
void advertisementCallback(BLEAdvertisement *bleAdvertisement){
  if(DEBUG_OUTPUT) Serial.printf("Found %s , RSSI: %d\n",bleAdvertisement->getBdAddr()->getAddressString(),bleAdvertisement->getRssi());
  if(bleAdvertisement->nameHasPrefix(NAME_PREFIX) && bleAdvertisement->getRssi()>rssi_limit){ // Filiter by name and rssi
    bool add_flag = true; // true if it's a newly discovered device
    for(int i=0;i<device_count;i++){ // Check if its a redundant device, store rssi value as bigger one
      if(strcmp(bleAdvertisement->getBdAddr()->getAddressString(),nearby_devices[i].addr) == 0){
        add_flag = false;
        if(bleAdvertisement->getRssi() > nearby_devices[i].rssi) nearby_devices[i].rssi = bleAdvertisement->getRssi();
        break;
      }
    }
    if(add_flag){ // to connect to a device, both BLE address type and address are needed.
      strcpy(nearby_devices[device_count].addr, bleAdvertisement->getBdAddr()->getAddressString());
      nearby_devices[device_count].addr_type = bleAdvertisement->getBdAddr()->getAddressType();
      nearby_devices[device_count].rssi = bleAdvertisement->getRssi();
      device_count++;
    }
  }
}

/*
 * Connected to BLE peripherial
 * Our device can only connect to one central. When connected, the peripherial will stop advertising.
 * Important: Call discoverGATTServices() here not in the main thread. 
 * Also, from here we use ble_busy_flag to control program flow.
 */
void deviceConnectedCallback(BLEStatus status, BLEDevice *device) {
  switch (status) {
    case BLE_STATUS_OK:
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(STATUS_LED, HIGH);
      ble_connected_flag = true;
      ble_connected_device = *device;
      if(DEBUG_OUTPUT) Serial.println("BLE device connected!");
      ble_busy_flag = false;
#ifdef epd1in54_V2_H // This is the init part for 1.54inch
      epd.LDirInit();
      drawEPDBackground(); // in order to clear old image, a full background redraw is required.
#endif
      break;
    default:
      Serial.println("Device connect failed!");
      break;
  }
}


/*
 * Disconnect from BLE peripherial
 */
void deviceDisconnectedCallback(BLEDevice * device) {
  if(DEBUG_OUTPUT) Serial.println("BLE device disconnected.");
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(STATUS_LED, LOW);
#ifdef epd1in54_V2_H // This is the init part for 1.54inch
  epd.Sleep();
#endif
  ble_connected_flag = false;
}

/*
 * This function is called whenever a service is discovered.
 * A peripheral might have more services than we need, and we cannot querry for specific service.
 * So we need to get all services, filiter them and save whatever we need for latter use.
 */
void gattServiceDiscovered(BLEStatus status, BLEDevice *device, BLEService *bleService){
  if(DEBUG_OUTPUT) Serial.println("gattServiceDiscovered");
  switch(status){
    case BLE_STATUS_OK:
      //Serial.print("Service Discovered: :");
      //Serial.println(bleService->getUUID()->getUuidString());
      if (bleService->matches(&NAME_UUID)) {
        //Serial.println("Found name service");
        ble_name_service = *bleService;
      }
      else if (bleService->matches(&BATTERY_UUID)) {
        //Serial.println("Found battery service");
        ble_battery_service = *bleService;
      }
      else if (bleService->matches(&UART_UUID)) {
        //Serial.println("Found uart service");
        ble_uart_service = *bleService;
      }
      break;
    case BLE_STATUS_DONE:
      //Serial.println("Service discovery finished");
      ble_busy_flag = false;
      break;
    default:
      Serial.println("Service discovery error");
      break;
  }

}

/*
 * For all the GATT queries, characteristic is what we want at last.
 * 
 */
void gattCharacteristicDiscovered(BLEStatus status, BLEDevice *device, BLECharacteristic *characteristic){
  if(DEBUG_OUTPUT) Serial.println("gattCharacteristicDiscovered");
  switch(status){
    case BLE_STATUS_OK:
      ///Serial.printf("Characteristic UUID: %s\n",characteristic->getUUID()->getUuidString());
      if(characteristic->matches(&NAME_CHAR_UUID)){
        //Serial.println("Found name characteristic.");
        ble_name_characteristic = *characteristic;
      }
      else if(characteristic->matches(&BATTERY_LEVEL_UUID)){
        //Serial.println("Found battery characteristic.");
        ble_battery_characteristic = *characteristic;
      }
      else if(characteristic->matches(&UART_TX_UUID)){
        //Serial.println("Found tx characteristic.");
        ble_tx_characteristic = *characteristic;
      }
      else if(characteristic->matches(&UART_RX_UUID)){
        //Serial.println("Found rx characteristic.");
        ble_rx_characteristic = *characteristic;
      }
      break;
    case BLE_STATUS_DONE:
      //Serial.println("Characteristics discovery done");
      ble_busy_flag = false;
      break;
    default:
      Serial.println("Characteristics discovery error");
      break;
  }
}

/*
 * Since there's no way to ensure which handle is sending values unless we add a enum flag before reading.
 * So we set all data received are strings by default.
 */
void gattReadCallback(BLEStatus status, BLEDevice *device, uint8_t *value, uint16_t length) {
  if(DEBUG_OUTPUT) Serial.printf("gattReadCallback: %s\n", (char*)value);
  if(length<BUFFER_SIZE){
//    memcpy((char*)buffer,(const char*)value,length);
    strcpy((char*)buffer,(const char*)value);
    buffer[length] = '\0';
    buffer_length = length+1;
  }
  else {
    memcpy(buffer,value,BUFFER_SIZE);
    buffer_length = BUFFER_SIZE;
  }
}

/*
 * Called when write done
 */
void gattWrittenCallback(BLEStatus status, BLEDevice *device){
  if(DEBUG_OUTPUT) Serial.println("gattWrittenCallback");
  delay(100);
  if(status == BLE_STATUS_OK)
    ble_busy_flag = false;
  else if(DEBUG_OUTPUT) Serial.println("OOPS!");
}

/*
 * Below functions are not used for now
 */
void gattSubscribedCallback(BLEStatus status, BLEDevice * device){
  if(DEBUG_OUTPUT) Serial.println("gattSubscribedCallback");

}

void gattCharacteristicNotification(BLEDevice *device, uint16_t value_handle, uint8_t *value, uint16_t length) {
  if(DEBUG_OUTPUT) Serial.printf("Notification: %s\n", value);
}

#endif

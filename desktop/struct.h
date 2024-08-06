#ifndef _STRUCT_H_
#define _STRUCT_H_

#include <BTstackLib.h> // BLE address format

/*
 * A type to contain which GPIO corespond to what message send to server
 */
typedef struct{
  int pin;
  const char* name;
} sensor_pin_t;

#define ARRAY_SIZE(x) sizeof(x)/sizeof(x[0])

typedef struct{
  BD_ADDR_TYPE  addr_type;
  char addr[19];
  int rssi;
} ble_adv_t;

/*
 * Standard battery service
 * Battery level is an integer between 0 and 100
 */
UUID BATTERY_UUID = UUID("180F");
UUID BATTERY_LEVEL_UUID = UUID("2A19");

/*
 * Use Nordic UART to send/receive data.
 * This way we can debug using standard tools.
 */
UUID UART_UUID = UUID("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");
UUID UART_TX_UUID = UUID("6E400003-B5A3-F393-E0A9-E50E24DCCA9E");
UUID UART_RX_UUID = UUID("6E400002-B5A3-F393-E0A9-E50E24DCCA9E");

/*
 * Since BTstack don't support extract device name from advertising data,
 * create an unique service for it.
 */
UUID NAME_UUID = UUID("DD5FF900-1989-A881-0604-0A4D6B6B0179");
UUID NAME_CHAR_UUID = UUID("DD5FF901-1989-A881-0604-0A4D6B6B0179");

/*   
 * Global buffer for BLE and MQTT read callback
 * Note that 600 bytes limit comes from BLE max MTU
 */
const int BUFFER_SIZE = 650;
uint8_t buffer[BUFFER_SIZE];
uint16_t buffer_length; // actual size used in program

/*
 * Variables for BLE
 */
char handheld_name[20];
char handheld_battery_level[4];
char handheld_value[20];
bool ble_connected_flag = false;
ble_adv_t *linked_handheld_device;

ble_adv_t nearby_devices[20]; // Suppose 20 devices are enough
int device_count = 0;
const int rssi_limit = -60; // opt out devices too far away
bool ble_busy_flag = false; // making program into blocking mode

#endif

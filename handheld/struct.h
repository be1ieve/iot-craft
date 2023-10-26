#ifndef _STRUCT_H_
#define _STRUCT_H_
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
 * Save handle ID For BLE read callback to identify.
 */
uint16_t batt_handle = 0;
uint16_t tx_handle = 0;
uint16_t rx_handle = 0;
uint16_t name_handle = 0;

/*
 * A buffer for receive data from ble.
 * Note that a standard BLE can only send 600 bytes at once. Larger data needs to be splited.
 * And JSON cannot transfer binary data by design. In order to send binary data, need to use base64 format. 
 * Base64 format will enlarge the size a lot, a 64*64px image will increase from 512 bytes to around 750 bytes.
 *
 * To create transferable data, create image c array file using image2lcd.exe as normal.
 * Then stripe the "Ox" and "," from C array using Notepad++, then find a HEX to Base64 online convertion.
 * 
*/
#define BUFFER_SIZE 650
char rx_buffer[BUFFER_SIZE];
uint16_t rx_size = 0;
bool rx_receiving_flag = false;

#endif

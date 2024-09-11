#ifndef _STRUCT_H_
#define _STRUCT_H_

/*
 * A type to contain which GPIO corespond to what message send to server
 */
typedef struct{
  const char* name;
  int rst_pin;
  int ss_pin;
} sensor_t;

#define ARRAY_SIZE(x) sizeof(x)/sizeof(x[0])

/*   
 * Global buffer for MQTT read callback
 * Note that 600 bytes limit comes from BLE max MTU
 */
const int BUFFER_SIZE = 600;
uint8_t buffer[BUFFER_SIZE];
uint16_t buffer_length; // actual size used in program

#endif

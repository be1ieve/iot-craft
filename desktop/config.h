#ifndef _CONFIG_H_
#define _CONFIG_H_

/*
 *  All devices must have the same NAME_PREFIX in order to distingish from massive BLE devices around.
 */
#define NAME_PREFIX "IOT-"

/*
 * Header will be a 30px heigh black banner with white text.
 * Font size is fixed to 20px high, max text length is 12 characters.
 */
String HEADER_TEXT = "IOT-Craft";

/*
 * For automatic name generation, we need something constant but differ from others: mac address.
 * But BTstack cannot access local address, DEVICE_NAME must be hard coded or use WiFi mac address instead.
 * Luckily on RPi pico w, Wifi mac address can be granted easily.
 */
char DEVICE_NAME[20] = "CUSTOM_NAME_HERE"; // Must start with NAME_PREFIX, or it will be overwritten using WiFi mac address

/*
 * WIFI access SSID and password
 * No luck if your WiFi needs to login using portal.
 */

#define WIFI_SSID "lemongrass"
#define WIFI_PASSWORD "0229035188"

/*
 * When a handheld device touches desktop device, some steps will happen:
 * 1. send combined data to MQTT_PREFIX + DEVICE_NAME + MQTT_TOPIC_NOTIFY
 * 2. read value from MQTT_PREFIX + DEVICE_NAME + MQTT_TOPIC_VALUE and displayed on screen
 * 3. read value from MQTT_PREFIX + HANDHELD_NAME + MQTT_TOPIC_VALUE and send to handheld device
 * 
 * A simple way to get the whole picture is subscribe MQTT_PREFIX with # wildcard
 * For example, default MQTT_PREFIX is "iot-craft/", and "/input" "/ouput" are places for sending and receiving data.
 * Subscribe to "iot-craft/#", will give you all the incomming and outgoing data, even what you sent.
 * "iot-craft/+/input" means all data sent to all devices, and "iot-craft/+/output" means all data from all devices.
 * If only interested in data from specific device, use "iot-craft/DEVICE_NAME/output".
 * And for sending command to each device, use "iot-craft/DEVICE_NAME/input".
*/
#define MQTT_SERVER "broker.hivemq.com" // https://www.hivemq.com/public-mqtt-broker/
#define MQTT_PORT 1883
#define MQTT_PREFIX "iot-craft/"
#define MQTT_TOPIC_OUTPUT "/output" // send data to server
#define MQTT_TOPIC_INPUT "/input" // receive value from server

#define MQTT_UPDATE_INTERVAL_US 1000000 // check for updates every 1 seconds

/*
 * Define pins used in contact sensor.
 * The first element is the GPIO id, the second element is the name to send out.
 */
sensor_pin_t SENSOR_PINS[]={{16,"SENSOR_1"},{18,"SENSOR_2"},{20,"SENSOR_3"}};

/*
 * A notification LED on GPIO 12
 */
#define STATUS_LED 12


#endif

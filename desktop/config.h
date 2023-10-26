#ifndef _CONFIG_H_
#define _CONFIG_H_

/*
 *  All devices must have the same NAME_PREFIX in order to distingish from massive BLE devices around.
 */
#define NAME_PREFIX "IOT-"
/*
 * For automatic name generation, we need something constant but differ from others: mac address.
 * But BTstack cannot access local address, DEVICE_NAME must be hard coded or use WiFi mac address instead.
 * Luckily on RPi pico w, Wifi mac address can be granted easily.
 */
char DEVICE_NAME[12] = "CUSTOM_NAME"; // Must start with NAME_PREFIX, or it will be overwritten using WiFi mac address

/*
 * WIFI access SSID and password
 * No luck if your WiFi needs to login using portal.
 */
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASSWORD"

/*
 * When a handheld device touches desktop device, some steps will happen:
 * 1. send combined data to MQTT_PREFIX + DEVICE_NAME + MQTT_TOPIC_NOTIFY
 * 2. read value from MQTT_PREFIX + DEVICE_NAME + MQTT_TOPIC_VALUE and displayed on screen
 * 3. read value from MQTT_PREFIX + HANDHELD_NAME + MQTT_TOPIC_VALUE and send to handheld device
 * 
 * A simple way to get the whole picture is subscribe MQTT_PREFIX with # wildcard
 * For example, if MQTT_PREFIX is "iot-craft/", subscribe "iot-craft/#"
*/
#define MQTT_SERVER "mqtt-dashboard.com" // https://www.hivemq.com/public-mqtt-broker/
#define MQTT_PREFIX "iot-craft/"
#define MQTT_TOPIC_OUTPUT "/output" // send data to server
#define MQTT_TOPIC_INPUT "/input" // receive value from server

#define MQTT_UPDATE_INTERVAL_US 5000000 // check for updates every 5 seconds

/*
 * Define pins used in contact sensor.
 * The first element is the GPIO id, the second element is the name to send out.
 */
sensor_pin_t SENSOR_PINS[]={{20,"Left"},{21,"Middle"},{22,"Right"}};

#endif

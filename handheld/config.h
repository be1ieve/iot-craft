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

#endif

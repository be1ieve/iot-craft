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

#endif

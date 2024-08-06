#ifndef _DISPLAY_H_
#define _DISPLAY_H_

/*
 * This file contains functions to work with 1.54 inch e-paper
 */

/*
 * For waveshare 1.54inch 200*200 b/w epaper module
 * https://www.waveshare.com/1.54inch-e-paper-module.htm
 * For migrating to Pi Pico, some additional pins must be defined:
 * In epdif.h, add custom pins in "pin definition" section
 * In epdif.cpp, enable custom pins inside "EpdIf::IfInit(void)"
*/
#include "epd1in54_V2.h"
#include "epdpaint.h"


/*
 * Limited image size and reuse it often
 */
unsigned char image[5000]; // (200*200)/8
Paint paint(image, 0, 0); // width should be the multiple of 8 
Epd epd;
#define COLORED     0
#define UNCOLORED   1

const uint8_t STANDBY_1Q_WIDTH = 56;
const uint8_t STANDBY_1Q_HEIGHT = 56;
const unsigned char STANDBY_1Q[392] = { /* 0X00,0X01,0X38,0X00,0X38,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,
0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X03,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFE,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X07,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFE,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFE,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X1F,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X3F,0XF0,0XFF,0XFF,0XFF,0XFF,0XFC,0X3F,0XF0,0XFF,
0XFF,0XFF,0XFF,0XFC,0X7F,0XE0,0XFF,0XFF,0XFF,0XFF,0XFC,0X7F,0XE0,0XFF,0XFF,0XFF,
0XFF,0XFC,0X7F,0XE1,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0XC3,0XFF,0XFF,0XFF,0XFF,0XFC,
0XFF,0XC7,0XFF,0XFF,0XFF,0XFF,0XFD,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFD,0XFF,0X9F,
0XFF,0XFE,0XFF,0XFF,0XFD,0XFF,0X3F,0XFF,0XF8,0X7F,0XFF,0XFF,0XFF,0X7F,0XFF,0XF0,
0X3F,0XFF,0XFF,0XFF,0X7F,0XFF,0XC0,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X3F,0XFF,
0XFF,0XFF,0XFF,0XFF,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,0X7F,0XFF,0XFF,0XFF,
0XFF,0XFC,0X01,0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XE0,
0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XC1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X87,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X7F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFD,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X7F,0XFF,
0XFF,0XFF,0XFF,0XFF,0XE0,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFC,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFA,0XDA,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,};

const uint8_t STANDBY_2Q_WIDTH = 56;
const uint8_t STANDBY_2Q_HEIGHT = 112;
const unsigned char STANDBY_2Q[784] = { /* 0X00,0X01,0X38,0X00,0X70,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,
0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X03,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFE,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X07,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFE,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFE,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X1F,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X3F,0XF0,0XFF,0XFF,0XFF,0XFF,0XFC,0X3F,0XF0,0XFF,
0XFF,0XFF,0XFF,0XFC,0X7F,0XE0,0XFF,0XFF,0XFF,0XFF,0XFC,0X7F,0XE0,0XFF,0XFF,0XFF,
0XFF,0XFC,0X7F,0XE1,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0XC3,0XFF,0XFF,0XFF,0XFF,0XFC,
0XFF,0XC7,0XFF,0XFF,0XFF,0XFF,0XFD,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFD,0XFF,0X9F,
0XFF,0XFE,0XFF,0XFF,0XFD,0XFF,0X3F,0XFF,0XF8,0X7F,0XFF,0XFF,0XFF,0X7F,0XFF,0XF0,
0X3F,0XFF,0XFF,0XFF,0X7F,0XFF,0XC0,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X3F,0XFF,
0XFF,0XFF,0XFF,0XFF,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,0X7F,0XFF,0XFF,0XFF,
0XFF,0XFC,0X01,0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XE0,
0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XC1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X87,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X7F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFD,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X7F,0XFF,
0XFF,0XFF,0XFF,0XFF,0XE0,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFC,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFA,0XDA,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0X2F,
0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X00,0X07,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,0X01,0XFF,
0XFF,0XFF,0XFF,0XFF,0XC0,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X00,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFC,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X01,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XE1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X87,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XC1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XF8,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X0F,
0XFF,0XFF,0XFF,0XFD,0XFF,0XFF,0X1F,0XFF,0XFF,0XFF,0XFC,0XFF,0XFF,0XBF,0XFF,0XFF,
0XFF,0XFE,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X1F,0XFF,0XFF,0XFF,0XFF,0XE7,0XFF,0X0F,0XFF,
0XFF,0XFF,0XFF,0XE7,0XFF,0X87,0XFF,0XFF,0XFF,0XFF,0XE7,0XFF,0X83,0XFF,0XFF,0XFF,
0XFF,0XE7,0XFF,0XC1,0XFF,0XFF,0XFF,0XFF,0XE3,0XFF,0XC0,0XFF,0XFF,0XFF,0XFF,0XE3,
0XFF,0XE0,0XFF,0XFF,0XFF,0XFF,0XE3,0XFF,0XE0,0X7F,0XFF,0XFF,0XFF,0XE1,0XFF,0XE0,
0X3F,0XFF,0XFF,0XFF,0XE1,0XFF,0XF0,0X1F,0XFF,0XFF,0XFF,0XE1,0XFF,0XF0,0X1F,0XFF,
0XFF,0XFF,0XE0,0XFF,0XF8,0X1F,0XFF,0XFF,0XFF,0XE0,0XFF,0XF8,0X1F,0XFF,0XFF,0XFF,
0XF1,0XFF,0XFC,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};

const uint8_t STANDBY_3Q_WIDTH = 112;
const uint8_t STANDBY_3Q_HEIGHT = 112;
const unsigned char STANDBY_3Q[1568] = { /* 0X00,0X01,0X70,0X00,0X70,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFE,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,
0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X07,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X0F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFC,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFC,0X3F,0XF0,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,
0X3F,0XF0,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X7F,0XE0,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X7F,0XE0,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X7F,0XE1,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0XC3,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0XC7,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFD,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFD,0XFF,0X9F,0XFF,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFD,
0XFF,0X3F,0XFF,0XF8,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7F,
0XFF,0XF0,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7F,0XFF,0XC0,
0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X3F,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X01,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XF8,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XE0,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XC1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X87,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X1F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFD,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X7F,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE0,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFA,0XDA,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X6D,0XBF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X00,0X1F,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X01,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XC0,0X2F,0XFF,0XFF,0XFF,0XFC,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X00,
0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,0X01,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0X00,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X01,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XE1,0XFF,0XFF,0XFF,0XFF,0XFE,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XE1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X87,0XFF,0XFF,0XFF,0XFF,0XFF,
0XF8,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC1,0XFF,0XFF,0XFF,0XFF,0XFF,0XE0,0X1F,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X3F,0XFF,0XFF,0XFF,0XFF,0X00,0X3F,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0XFF,0XFE,0X00,0X7F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFC,0X0F,0XFF,0XFF,0XFF,0XFC,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFE,0X0F,0XFF,0XFF,0XFF,0XF8,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFD,0XFF,0XFF,0X1F,
0XFF,0XFF,0XFF,0XF8,0X07,0XFF,0XFE,0XFF,0XFF,0XFF,0XFC,0XFF,0XFF,0XBF,0XFF,0XFF,
0XFF,0XFC,0X0F,0XFF,0XFC,0XFF,0XFF,0XFF,0XFE,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,
0X1F,0XFF,0XF9,0XFF,0XBF,0XFF,0XFE,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XBF,0XFF,
0XF9,0XFF,0XBF,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF3,0XFF,
0X3F,0XFF,0XFF,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE3,0XFF,0X3F,0XE7,
0XFF,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC3,0XFF,0X3F,0XE7,0XFF,0X87,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X87,0XFE,0X3F,0XE7,0XFF,0X83,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X07,0XFE,0X3F,0XE7,0XFF,0XC1,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X0F,0XFC,0X7F,0XE3,0XFF,0XC0,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0X0F,0XFC,0X7F,0XE3,0XFF,0XE0,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0X9F,0XF8,0X7F,0XE3,0XFF,0XE0,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,
0X7F,0XE1,0XFF,0XE0,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,0X7F,0XE1,
0XFF,0XF0,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X7F,0XE1,0XFF,0XF0,
0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X7F,0XE0,0XFF,0XF8,0X1F,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE0,0X7F,0XE0,0XFF,0XF8,0X1F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XE0,0X7F,0XF1,0XFF,0XFC,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XE0,0X7F,0XFF,0XFF,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XC0,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,
0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};

const uint8_t STANDBY_4Q_WIDTH = 112;
const uint8_t STANDBY_4Q_HEIGHT = 112;
const unsigned char STANDBY_4Q[1568] = { /* 0X00,0X01,0X70,0X00,0X70,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFE,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X7F,0XFF,0XFF,0XFE,
0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,0X3F,0XFF,0X0F,0XFE,0X07,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X1F,0XFF,0X0F,0XFE,0X0F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X1F,0XFF,0X0F,0XFE,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XF0,0X0F,0XFF,0X0F,0XFE,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XF8,0X0F,0XFF,0X8F,0XFE,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,
0X0F,0XFF,0X8F,0XFC,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X07,0XFF,
0X8F,0XFC,0X3F,0XF0,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X07,0XFF,0XCF,0XFC,
0X3F,0XF0,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X03,0XFF,0XCF,0XFC,0X7F,0XE0,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X83,0XFF,0XCF,0XFC,0X7F,0XE0,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC3,0XFF,0XEF,0XFC,0X7F,0XE1,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XE1,0XFF,0XEF,0XFC,0XFF,0XC3,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XE1,0XFF,0XEF,0XFC,0XFF,0XC7,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XF0,0XFF,0XFF,0XFD,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,0XFF,
0XFF,0XFD,0XFF,0X9F,0XFF,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X7F,0XFF,0XFD,
0XFF,0X3F,0XFF,0XF8,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X7F,0XFF,0XFF,0XFF,0X7F,
0XFF,0XF0,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,0X7F,0XFF,0XC0,
0X1F,0XFF,0XFF,0XFF,0XF0,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X3F,0XFF,
0XFF,0XFF,0XF0,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X3F,0XFF,0XFF,0XFF,
0XF0,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,0X7F,0XFF,0XFF,0XFF,0XF8,0X1F,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X01,0XFF,0XFF,0XFF,0XFF,0XFE,0X0F,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XF8,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0X87,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XE0,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XE1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XC1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF9,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X87,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X1F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X7F,0XFF,0XFF,0XFF,0XFF,0X8F,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFD,0XFF,0XFF,0XFF,0XFF,0XFF,0X01,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X01,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X00,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XC0,0X00,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X7F,0XFF,
0XFF,0XFF,0XF0,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE0,0X3F,0XFF,0XFF,0XFF,
0XFF,0XF7,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFA,0XDA,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X6D,0XBF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X00,0X1F,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X01,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XC0,0X2F,0XFF,0XFF,0XFF,0XFC,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X00,
0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,0X01,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0X00,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X01,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XE1,0XFF,0XFF,0XFF,0XFF,0XFE,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XE1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X87,0XFF,0XFF,0XFF,0XFF,0XFF,
0XF8,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC1,0XFF,0XFF,0XFF,0XFF,0XFF,0XE0,0X1F,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X3F,0XFF,0XFF,0XFF,0XFF,0X00,0X3F,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0XFF,0XFE,0X00,0X7F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFC,0X0F,0XFF,0XFF,0XFF,0XFC,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFE,0X0F,0XFF,0XFF,0XFF,0XF8,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFD,0XFF,0XFF,0X1F,
0XFF,0XFF,0XFF,0XF8,0X07,0XFF,0XFE,0XFF,0XFF,0XFF,0XFC,0XFF,0XFF,0XBF,0XFF,0XFF,
0XFF,0XFC,0X0F,0XFF,0XFC,0XFF,0XFF,0XFF,0XFE,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,
0X1F,0XFF,0XF9,0XFF,0XBF,0XFF,0XFE,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XBF,0XFF,
0XF9,0XFF,0XBF,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF3,0XFF,
0X3F,0XFF,0XFF,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE3,0XFF,0X3F,0XE7,
0XFF,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC3,0XFF,0X3F,0XE7,0XFF,0X87,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X87,0XFE,0X3F,0XE7,0XFF,0X83,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X07,0XFE,0X3F,0XE7,0XFF,0XC1,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X0F,0XFC,0X7F,0XE3,0XFF,0XC0,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0X0F,0XFC,0X7F,0XE3,0XFF,0XE0,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0X9F,0XF8,0X7F,0XE3,0XFF,0XE0,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,
0X7F,0XE1,0XFF,0XE0,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,0X7F,0XE1,
0XFF,0XF0,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X7F,0XE1,0XFF,0XF0,
0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X7F,0XE0,0XFF,0XF8,0X1F,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE0,0X7F,0XE0,0XFF,0XF8,0X1F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XE0,0X7F,0XF1,0XFF,0XFC,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XE0,0X7F,0XFF,0XFF,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XC0,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,
0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};

/*
 * Below functions are bounded with waveshare 1.54inch e-Paper display
 * Changing rotation angle or even change display needs to change everything. 
 */
#ifdef epd1in54_V2_H
/*
 * Draw something after power-on and before connected.
 */
/*
void drawEPDWelcome(){
  // put an image at center
  epd.SetFrameMemory(IMAGE_LOGO, 100-int(IMAGE_LOGO_WIDTH/2), 100-int(IMAGE_LOGO_HEIGHT/2), IMAGE_LOGO_WIDTH, IMAGE_LOGO_HEIGHT);
  // write DEVICE_NAME at bottom, 16px height and full 200px width in case the name is too long.
  paint.SetWidth(200);
  paint.SetHeight(16);
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(4,4, DEVICE_NAME, &Font16, COLORED);
  epd.SetFrameMemory(image,0,183, 200,16);
  epd.DisplayFrame();
}
*/

/*
 * This background is for partial update function. a whole 200*200px image applied.
 * Note that there's no specific buffer for background image. So we have to display the image alone then process the rest.
 */
void drawEPDBackground(){
  paint.SetWidth(200);
  paint.SetHeight(200);
  paint.Clear(UNCOLORED);

  // Draw a 30px height banner on top
  int textOffset = 100-HEADER_TEXT.length()*7;
  if(textOffset < 0) textOffset = 0;
  paint.DrawFilledRectangle(0,0,200,30,COLORED);
  char tmpChar[HEADER_TEXT.length()+1];
  HEADER_TEXT.toCharArray(tmpChar, HEADER_TEXT.length()+1);
  paint.DrawStringAt(textOffset, 8, tmpChar, &Font20, UNCOLORED);
  textOffset = 100-int(strlen(DEVICE_NAME)*5.5);
  paint.DrawStringAt(textOffset,183, DEVICE_NAME, &Font16, COLORED);
  epd.DisplayPartBaseImage(image);
}
#endif // epd1in54_V2_H

#endif // _DISPLAY_H_

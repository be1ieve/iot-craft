#ifndef _POKER_H_
#define _POKER_H_

/*
 * This file contains images and function bounded with specific screen: waveshare 1.54 inch epaper display.
 * Image data can be created using image2lcd.exe. Note the color should be inverted and save as C array without header.
 * To display, send: {"poker":"SUIT+NUMBER"}, for example, Diamond 3 will be: {"poker":"D03"} 
 * Suits: C, D, H, S, and J
 * Numbers: 1 to 13
 */

#include "display.h" // required to show image

// Where to put poker image and text
const uint8_t POKER_IMAGE_CENTER_X = 50;
const uint8_t POKER_IMAGE_CENTER_Y = 100;
const uint8_t POKER_TEXT_CENTER_X = 150;
const uint8_t POKER_TEXT_CENTER_Y = 100;

/*
 * Poker club, 64*64px
 */
const uint8_t POKER_CLUB_WIDTH = 64;
const uint8_t POKER_CLUB_HEIGHT = 64;
const unsigned char POKER_CLUB[512] = { /* 0X00,0X01,0X40,0X00,0X40,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XC0,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X01,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFE,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X00,0X00,0X7F,0XFF,0XFF,
0XFF,0XFF,0XF8,0X00,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XF8,0X00,0X00,0X1F,0XFF,0XFF,
0XFF,0XFF,0XF0,0X00,0X00,0X1F,0XFF,0XFF,0XFF,0XFF,0XF0,0X00,0X00,0X0F,0XFF,0XFF,
0XFF,0XFF,0XE0,0X00,0X00,0X0F,0XFF,0XFF,0XFF,0XFF,0XE0,0X00,0X00,0X0F,0XFF,0XFF,
0XFF,0XFF,0XE0,0X00,0X00,0X0F,0XFF,0XFF,0XFF,0XFF,0XE0,0X00,0X00,0X0F,0XFF,0XFF,
0XFF,0XFF,0XE0,0X00,0X00,0X07,0XFF,0XFF,0XFF,0XFF,0XE0,0X00,0X00,0X0F,0XFF,0XFF,
0XFF,0XFF,0XE0,0X00,0X00,0X0F,0XFF,0XFF,0XFF,0XFF,0XE0,0X00,0X00,0X0F,0XFF,0XFF,
0XFF,0XFF,0XF0,0X00,0X00,0X0F,0XFF,0XFF,0XFF,0XFF,0XF0,0X00,0X00,0X1F,0XFF,0XFF,
0XFF,0XFF,0XF8,0X00,0X00,0X1F,0XFF,0XFF,0XFF,0XFF,0XF8,0X00,0X00,0X3F,0XFF,0XFF,
0XFF,0XFF,0XFC,0X00,0X00,0X7F,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,0X00,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0X00,0X01,0XFF,0XFF,0XFF,0XFF,0XE0,0X07,0XC0,0X03,0XC0,0X0F,0XFF,
0XFF,0X80,0X01,0XF0,0X1F,0X00,0X03,0XFF,0XFF,0X00,0X00,0XF8,0X1E,0X00,0X00,0XFF,
0XFE,0X00,0X00,0X78,0X1C,0X00,0X00,0X7F,0XFC,0X00,0X00,0X30,0X08,0X00,0X00,0X7F,
0XF8,0X00,0X00,0X00,0X00,0X00,0X00,0X3F,0XF8,0X00,0X00,0X00,0X00,0X00,0X00,0X1F,
0XF0,0X00,0X00,0X00,0X00,0X00,0X00,0X1F,0XF0,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,
0XF0,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,
0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,
0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,
0XF0,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,0XF0,0X00,0X00,0X00,0X00,0X00,0X00,0X1F,
0XF0,0X00,0X00,0X08,0X20,0X00,0X00,0X1F,0XF8,0X00,0X00,0X18,0X30,0X00,0X00,0X1F,
0XF8,0X00,0X00,0X1C,0X38,0X00,0X00,0X3F,0XFC,0X00,0X00,0X3C,0X78,0X00,0X00,0X7F,
0XFE,0X00,0X00,0X78,0X3C,0X00,0X00,0XFF,0XFF,0X00,0X00,0XF8,0X3E,0X00,0X01,0XFF,
0XFF,0XC0,0X01,0XF8,0X3F,0X80,0X03,0XFF,0XFF,0XF0,0X0F,0XF8,0X3F,0XE0,0X1F,0XFF,
0XFF,0XFF,0XFF,0XF8,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X1F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XF0,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X1F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XF0,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE0,0X0F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XE0,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0X07,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XC0,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0X03,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0X80,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XBF,0XFB,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};

/*
 * Poker diamond, 64*64px
 */
const uint8_t POKER_DIAMOND_WIDTH = 64;
const uint8_t POKER_DIAMOND_HEIGHT = 64;
const unsigned char POKER_DIAMOND[512] = { /* 0X00,0X01,0X40,0X00,0X40,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFC,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XF0,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X07,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XE0,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0X03,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0X80,0X01,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X00,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0X00,0X00,0X7F,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,0X00,0X7F,0XFF,0XFF,
0XFF,0XFF,0XFC,0X00,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XF8,0X00,0X00,0X1F,0XFF,0XFF,
0XFF,0XFF,0XF8,0X00,0X00,0X0F,0XFF,0XFF,0XFF,0XFF,0XF0,0X00,0X00,0X07,0XFF,0XFF,
0XFF,0XFF,0XE0,0X00,0X00,0X03,0XFF,0XFF,0XFF,0XFF,0XC0,0X00,0X00,0X01,0XFF,0XFF,
0XFF,0XFF,0X80,0X00,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0X00,0X00,0X00,0X00,0XFF,0XFF,
0XFF,0XFE,0X00,0X00,0X00,0X00,0X7F,0XFF,0XFF,0XFC,0X00,0X00,0X00,0X00,0X3F,0XFF,
0XFF,0XF8,0X00,0X00,0X00,0X00,0X1F,0XFF,0XFF,0XF0,0X00,0X00,0X00,0X00,0X0F,0XFF,
0XFF,0XE0,0X00,0X00,0X00,0X00,0X07,0XFF,0XFF,0XC0,0X00,0X00,0X00,0X00,0X03,0XFF,
0XFF,0X80,0X00,0X00,0X00,0X00,0X01,0XFF,0XFF,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,
0XFE,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0XFC,0X00,0X00,0X00,0X00,0X00,0X00,0X3F,
0XFE,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0XFF,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,
0XFF,0XC0,0X00,0X00,0X00,0X00,0X01,0XFF,0XFF,0XE0,0X00,0X00,0X00,0X00,0X03,0XFF,
0XFF,0XF0,0X00,0X00,0X00,0X00,0X0F,0XFF,0XFF,0XF8,0X00,0X00,0X00,0X00,0X1F,0XFF,
0XFF,0XFC,0X00,0X00,0X00,0X00,0X3F,0XFF,0XFF,0XFE,0X00,0X00,0X00,0X00,0X7F,0XFF,
0XFF,0XFF,0X00,0X00,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0X80,0X00,0X00,0X01,0XFF,0XFF,
0XFF,0XFF,0XC0,0X00,0X00,0X03,0XFF,0XFF,0XFF,0XFF,0XE0,0X00,0X00,0X03,0XFF,0XFF,
0XFF,0XFF,0XE0,0X00,0X00,0X07,0XFF,0XFF,0XFF,0XFF,0XF0,0X00,0X00,0X0F,0XFF,0XFF,
0XFF,0XFF,0XF8,0X00,0X00,0X1F,0XFF,0XFF,0XFF,0XFF,0XFC,0X00,0X00,0X3F,0XFF,0XFF,
0XFF,0XFF,0XFE,0X00,0X00,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X00,0X7F,0XFF,0XFF,
0XFF,0XFF,0XFF,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X01,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XC0,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE0,0X03,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XE0,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X0F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XF8,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFC,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};

/*
 * Poker heart, 64*64px
 */
const uint8_t POKER_HEART_WIDTH = 64;
const uint8_t POKER_HEART_HEIGHT = 64;
const unsigned char POKER_HEART[512] = { /* 0X00,0X01,0X40,0X00,0X40,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XF8,0X0F,0XFF,0XFF,0XF0,0X1F,0XFF,0XFF,0XC0,0X01,0XFF,0XFF,0X80,0X03,0XFF,
0XFF,0X00,0X00,0X7F,0XFE,0X00,0X01,0XFF,0XFE,0X00,0X00,0X3F,0XF8,0X00,0X00,0X7F,
0XFC,0X00,0X00,0X1F,0XF0,0X00,0X00,0X3F,0XF8,0X00,0X00,0X0F,0XE0,0X00,0X00,0X1F,
0XF0,0X00,0X00,0X07,0XE0,0X00,0X00,0X0F,0XE0,0X00,0X00,0X03,0XC0,0X00,0X00,0X0F,
0XE0,0X00,0X00,0X03,0X80,0X00,0X00,0X07,0XC0,0X00,0X00,0X01,0X80,0X00,0X00,0X03,
0XC0,0X00,0X00,0X01,0X00,0X00,0X00,0X03,0X80,0X00,0X00,0X01,0X00,0X00,0X00,0X03,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X03,
0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X03,
0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X07,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X07,
0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,0XF0,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,
0XF0,0X00,0X00,0X00,0X00,0X00,0X00,0X1F,0XF8,0X00,0X00,0X00,0X00,0X00,0X00,0X3F,
0XFC,0X00,0X00,0X00,0X00,0X00,0X00,0X3F,0XFE,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,
0XFF,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XFF,0X80,0X00,0X00,0X00,0X00,0X01,0XFF,
0XFF,0XC0,0X00,0X00,0X00,0X00,0X03,0XFF,0XFF,0XE0,0X00,0X00,0X00,0X00,0X07,0XFF,
0XFF,0XF0,0X00,0X00,0X00,0X00,0X0F,0XFF,0XFF,0XF8,0X00,0X00,0X00,0X00,0X1F,0XFF,
0XFF,0XFC,0X00,0X00,0X00,0X00,0X3F,0XFF,0XFF,0XFC,0X00,0X00,0X00,0X00,0X7F,0XFF,
0XFF,0XFE,0X00,0X00,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0X00,0X00,0X00,0X01,0XFF,0XFF,
0XFF,0XFF,0X80,0X00,0X00,0X03,0XFF,0XFF,0XFF,0XFF,0XC0,0X00,0X00,0X07,0XFF,0XFF,
0XFF,0XFF,0XE0,0X00,0X00,0X0F,0XFF,0XFF,0XFF,0XFF,0XF0,0X00,0X00,0X1F,0XFF,0XFF,
0XFF,0XFF,0XF8,0X00,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFC,0X00,0X00,0X7F,0XFF,0XFF,
0XFF,0XFF,0XFE,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X00,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0X80,0X01,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X03,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XC0,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE0,0X0F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XF0,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XF8,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X7F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};

/*
 * Poker joker, 64*64px
 */
const uint8_t POKER_JOKER_WIDTH = 64;
const uint8_t POKER_JOKER_HEIGHT = 64;
const unsigned char POKER_JOKER[512] = { /* 0X00,0X01,0X40,0X00,0X40,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X0F,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0X00,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X1F,0X83,0XFF,0XFF,
0XFF,0XFF,0XFF,0XF8,0X3F,0XC1,0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,0X7F,0XE0,0XFF,0XFF,
0XFF,0XFF,0XFF,0XF0,0XFF,0XF0,0X7F,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XF8,0X7F,0XFF,
0XFF,0XFF,0XFF,0XE1,0XFF,0XFC,0X3F,0XFF,0XFF,0XFF,0XE3,0XE3,0XFF,0XFC,0X3F,0XFF,
0XFF,0XFF,0X80,0X03,0XFF,0XE2,0X1F,0XFF,0XFF,0XFC,0X00,0X07,0XFF,0X80,0X1F,0XFF,
0XFF,0XF8,0X00,0X07,0XFF,0X00,0X1F,0XFF,0XFF,0XF0,0X7F,0X07,0XFE,0X00,0X1F,0XFF,
0XFF,0XE1,0XFF,0XCF,0XFE,0X7C,0X1F,0XFF,0XFF,0XC3,0XFF,0XEF,0XFD,0XFE,0X0F,0XFF,
0XFF,0X87,0XFF,0XFF,0XFF,0XFF,0X87,0XFF,0XFF,0X87,0XFF,0XFF,0XFF,0XFF,0X87,0XFF,
0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XC3,0XFF,0XFF,0X0F,0X83,0XFF,0XFF,0XFF,0XE3,0XFF,
0XFF,0X1E,0X01,0XFF,0XFF,0X81,0XE1,0XFF,0XFF,0X1E,0X00,0XFF,0XFF,0X00,0XE1,0XFF,
0XFF,0X1C,0X30,0XFF,0XFE,0X00,0X31,0XFF,0XFF,0X18,0X78,0X7F,0XFE,0X18,0X11,0XFF,
0XFF,0X18,0X78,0X00,0X00,0X3E,0X10,0XFF,0XFF,0X10,0XFC,0X00,0X00,0X7F,0X00,0XFF,
0XFF,0X01,0XFC,0X00,0X00,0X7F,0X00,0XFF,0XFF,0X01,0XF8,0X00,0X00,0X7F,0X80,0XFF,
0XFF,0X03,0XF8,0X7F,0XFC,0X3F,0XC0,0XFF,0XFF,0X87,0XF8,0XFF,0XFC,0X3F,0XE1,0XFF,
0XFF,0X87,0XF8,0XFF,0XFE,0X3F,0XE1,0XFF,0XFF,0XCF,0XF8,0XFF,0XFE,0X3F,0XF3,0XFF,
0XFF,0XDF,0XF8,0XFF,0XFE,0X3F,0XFB,0XFF,0XFF,0XFF,0XF8,0XFF,0XFE,0X3F,0XFF,0XFF,
0XFF,0XFF,0XF8,0XFF,0XFC,0X3F,0XFF,0XFF,0XFF,0XFF,0XF8,0XFF,0XFC,0X3F,0XFF,0XFF,
0XFF,0XFF,0XF8,0X7F,0XFC,0X7F,0XFF,0XFF,0XFF,0XFF,0XFC,0X70,0X1C,0X7F,0XFF,0XFF,
0XFF,0XFF,0XFC,0X38,0X38,0X7F,0XFF,0XFF,0XFF,0XFF,0XFC,0X3F,0XF0,0XFF,0XFF,0XFF,
0XFF,0XFF,0XF0,0X1F,0XF0,0X1F,0XFF,0XFF,0XFF,0XFF,0X80,0X0F,0XC0,0X07,0XFF,0XFF,
0XFF,0XFE,0X00,0X00,0X00,0X01,0XFF,0XFF,0XFF,0XFC,0X03,0X80,0X07,0X80,0X7F,0XFF,
0XFF,0XF8,0X3F,0XE0,0X0F,0XF0,0X3F,0XFF,0XFF,0XF0,0XFF,0XF8,0X7F,0XFC,0X3F,0XFF,
0XFF,0XF1,0XFF,0XFF,0XFF,0XFE,0X1F,0XFF,0XFF,0XF0,0X07,0XFF,0XFF,0X80,0X1F,0XFF,
0XFF,0XF0,0X01,0XFF,0XFE,0X00,0X1F,0XFF,0XFF,0XF8,0X00,0XFF,0XFE,0X00,0X3F,0XFF,
0XFF,0XFF,0XE0,0XFF,0XFC,0X03,0XFF,0XFF,0XFF,0XFF,0XF8,0XFE,0X7C,0X3F,0XFF,0XFF,
0XFF,0XFF,0XF8,0XF0,0X1E,0X3F,0XFF,0XFF,0XFF,0XFF,0XF0,0XE0,0X0E,0X3F,0XFF,0XFF,
0XFF,0XFF,0XF0,0X80,0X02,0X3F,0XFF,0XFF,0XFF,0XFF,0XF0,0X07,0XC0,0X3F,0XFF,0XFF,
0XFF,0XFF,0XF8,0X0F,0XE0,0X3F,0XFF,0XFF,0XFF,0XFF,0XFC,0X3F,0XF8,0X7F,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,};

/*
 * Poker spade, 64*64px
 */
const uint8_t POKER_SPADE_WIDTH = 64;
const uint8_t POKER_SPADE_HEIGHT = 64;
const unsigned char POKER_SPADE[512] = { /* 0X00,0X01,0X40,0X00,0X40,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFC,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,0X0F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XF0,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X07,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XE0,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0X03,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0X80,0X01,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X00,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0X00,0X00,0X7F,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,0X00,0X3F,0XFF,0XFF,
0XFF,0XFF,0XFC,0X00,0X00,0X1F,0XFF,0XFF,0XFF,0XFF,0XF8,0X00,0X00,0X1F,0XFF,0XFF,
0XFF,0XFF,0XF0,0X00,0X00,0X0F,0XFF,0XFF,0XFF,0XFF,0XE0,0X00,0X00,0X07,0XFF,0XFF,
0XFF,0XFF,0XC0,0X00,0X00,0X03,0XFF,0XFF,0XFF,0XFF,0X80,0X00,0X00,0X01,0XFF,0XFF,
0XFF,0XFF,0X00,0X00,0X00,0X00,0XFF,0XFF,0XFF,0XFE,0X00,0X00,0X00,0X00,0X7F,0XFF,
0XFF,0XFC,0X00,0X00,0X00,0X00,0X3F,0XFF,0XFF,0XF8,0X00,0X00,0X00,0X00,0X1F,0XFF,
0XFF,0XF0,0X00,0X00,0X00,0X00,0X0F,0XFF,0XFF,0XE0,0X00,0X00,0X00,0X00,0X07,0XFF,
0XFF,0XC0,0X00,0X00,0X00,0X00,0X07,0XFF,0XFF,0X80,0X00,0X00,0X00,0X00,0X03,0XFF,
0XFF,0X80,0X00,0X00,0X00,0X00,0X01,0XFF,0XFF,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,
0XFE,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0XFE,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,
0XFC,0X00,0X00,0X00,0X00,0X00,0X00,0X3F,0XFC,0X00,0X00,0X00,0X00,0X00,0X00,0X3F,
0XF8,0X00,0X00,0X00,0X00,0X00,0X00,0X1F,0XF8,0X00,0X00,0X00,0X00,0X00,0X00,0X1F,
0XF8,0X00,0X00,0X00,0X00,0X00,0X00,0X1F,0XF8,0X00,0X00,0X00,0X00,0X00,0X00,0X1F,
0XF8,0X00,0X00,0X00,0X00,0X00,0X00,0X1F,0XF8,0X00,0X00,0X00,0X00,0X00,0X00,0X1F,
0XF8,0X00,0X00,0X00,0X00,0X00,0X00,0X1F,0XFC,0X00,0X00,0X00,0X00,0X00,0X00,0X1F,
0XFC,0X00,0X00,0X00,0X00,0X00,0X00,0X3F,0XFC,0X00,0X00,0X00,0X00,0X00,0X00,0X3F,
0XFE,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0XFF,0X00,0X00,0X02,0X20,0X00,0X00,0X7F,
0XFF,0X80,0X00,0X06,0X20,0X00,0X00,0XFF,0XFF,0XC0,0X00,0X0E,0X30,0X00,0X01,0XFF,
0XFF,0XE0,0X00,0X1C,0X3C,0X00,0X03,0XFF,0XFF,0XF0,0X00,0X7C,0X3E,0X00,0X0F,0XFF,
0XFF,0XFE,0X03,0XFC,0X1F,0XC0,0X7F,0XFF,0XFF,0XFF,0XFF,0XFC,0X1F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XF8,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X0F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XF0,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X07,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XE0,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE0,0X03,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XE0,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0X01,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XCF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0XFF,0XFF,0XFF,
};

/*
 * 32*64px text
 */
const uint8_t POKER_A_WIDTH = 32;
const uint8_t POKER_A_HEIGHT = 64;
const unsigned char POKER_A[256] = { /* 0X00,0X01,0X20,0X00,0X40,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X3F,0XFF,
0XFF,0XFC,0X1F,0XFF,0XFF,0XFC,0X1F,0XFF,0XFF,0XFC,0X1F,0XFF,0XFF,0XF8,0X1F,0XFF,
0XFF,0XF8,0X0F,0XFF,0XFF,0XF8,0X0F,0XFF,0XFF,0XF8,0X0F,0XFF,0XFF,0XF8,0X0F,0XFF,
0XFF,0XF1,0X8F,0XFF,0XFF,0XF1,0X87,0XFF,0XFF,0XF1,0X87,0XFF,0XFF,0XF1,0XC7,0XFF,
0XFF,0XE1,0XC7,0XFF,0XFF,0XE3,0XC3,0XFF,0XFF,0XE3,0XC3,0XFF,0XFF,0XE3,0XC3,0XFF,
0XFF,0XE3,0XE3,0XFF,0XFF,0XC3,0XE3,0XFF,0XFF,0XC7,0XE1,0XFF,0XFF,0XC7,0XE1,0XFF,
0XFF,0XC7,0XE1,0XFF,0XFF,0XC7,0XF1,0XFF,0XFF,0X87,0XF1,0XFF,0XFF,0X8F,0XF0,0XFF,
0XFF,0X8F,0XF0,0XFF,0XFF,0X8F,0XF0,0XFF,0XFF,0X8F,0XF8,0XFF,0XFF,0X0F,0XF8,0X7F,
0XFF,0X1F,0XF8,0X7F,0XFF,0X1F,0XF8,0X7F,0XFF,0X0F,0XF8,0X7F,0XFE,0X0F,0XF0,0X7F,
0XFE,0X00,0X00,0X3F,0XFE,0X00,0X00,0X3F,0XFE,0X00,0X00,0X3F,0XFE,0X00,0X00,0X3F,
0XFC,0X3F,0XFC,0X3F,0XFC,0X3F,0XFE,0X1F,0XFC,0X3F,0XFE,0X1F,0XFC,0X7F,0XFE,0X1F,
0XFC,0X7F,0XFE,0X1F,0XF8,0X7F,0XFE,0X0F,0XF8,0X7F,0XFF,0X0F,0XF8,0X7F,0XFF,0X0F,
0XF8,0X7F,0XFF,0X0F,0XF0,0XFF,0XFF,0X0F,0XF0,0XFF,0XFF,0X07,0XF0,0XFF,0XFF,0X87,
0XF0,0XFF,0XFF,0X87,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};


/*
 * 32*64px text
 */
const uint8_t POKER_1_WIDTH = 32;
const uint8_t POKER_1_HEIGHT = 64;
const unsigned char POKER_1[256] = { /* 0X00,0X01,0X20,0X00,0X40,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X1F,0XFF,0XFF,0XFF,0X1F,0XFF,
0XFF,0XFC,0X0F,0XFF,0XFF,0XF8,0X07,0XFF,0XFF,0XE0,0X07,0XFF,0XFF,0XC0,0X07,0XFF,
0XFF,0X00,0X07,0XFF,0XFE,0X00,0X07,0XFF,0XFC,0X00,0X07,0XFF,0XF8,0X00,0X07,0XFF,
0XE0,0X0C,0X07,0XFF,0XE0,0X3C,0X07,0XFF,0XE0,0X7C,0X07,0XFF,0XE1,0XFC,0X07,0XFF,
0XE3,0XFC,0X07,0XFF,0XEF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,
0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,
0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,
0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,
0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,
0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,
0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,
0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,
0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,
0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X07,0XFF,0XFF,0XF8,0X03,0XFF,0XE0,0X00,0X00,0X01,
0XE0,0X00,0X00,0X01,0XE0,0X00,0X00,0X01,0XE0,0X00,0X00,0X01,0XE0,0X00,0X00,0X03,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};

/*
 * 32*64px text
 */
const uint8_t POKER_2_WIDTH = 32;
const uint8_t POKER_2_HEIGHT = 64;
const unsigned char POKER_2[256] = { /* 0X00,0X01,0X20,0X00,0X40,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XF8,0X3F,0XFF,0XFF,0XC0,0X0F,0XFF,0XFE,0X00,0X01,0XFF,0XFC,0X00,0X00,0XFF,
0XF0,0X00,0X00,0X7F,0XE0,0X00,0X00,0X3F,0XC0,0X00,0X00,0X3F,0XC0,0X7F,0XC0,0X1F,
0XC1,0XFF,0XE0,0X1F,0XC3,0XFF,0XF0,0X0F,0XEF,0XFF,0XF8,0X0F,0XFF,0XFF,0XFC,0X0F,
0XFF,0XFF,0XFC,0X0F,0XFF,0XFF,0XFC,0X0F,0XFF,0XFF,0XFC,0X0F,0XFF,0XFF,0XFC,0X0F,
0XFF,0XFF,0XFC,0X0F,0XFF,0XFF,0XFC,0X0F,0XFF,0XFF,0XFC,0X0F,0XFF,0XFF,0XFC,0X0F,
0XFF,0XFF,0XFC,0X0F,0XFF,0XFF,0XFC,0X0F,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0XF8,0X1F,
0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0XF0,0X3F,0XFF,0XFF,0XF0,0X3F,0XFF,0XFF,0XE0,0X7F,
0XFF,0XFF,0XE0,0X7F,0XFF,0XFF,0XC0,0XFF,0XFF,0XFF,0X80,0XFF,0XFF,0XFF,0X81,0XFF,
0XFF,0XFF,0X03,0XFF,0XFF,0XFE,0X03,0XFF,0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X0F,0XFF,
0XFF,0XF8,0X0F,0XFF,0XFF,0XF0,0X1F,0XFF,0XFF,0XE0,0X3F,0XFF,0XFF,0XE0,0X7F,0XFF,
0XFF,0XC0,0X7F,0XFF,0XFF,0X80,0XFF,0XFF,0XFF,0X01,0XFF,0XFF,0XFE,0X03,0XFF,0XFF,
0XFC,0X03,0XFF,0XFF,0XFC,0X0F,0XFF,0XFF,0XF8,0X0F,0XFF,0XFF,0XF0,0X1F,0XFF,0XFF,
0XE0,0X3F,0XFF,0XFF,0XC0,0X1F,0XFF,0XFF,0XC0,0X00,0X00,0X07,0XC0,0X00,0X00,0X01,
0XC0,0X00,0X00,0X01,0XC0,0X00,0X00,0X01,0XC0,0X00,0X00,0X01,0XC0,0X00,0X00,0X01,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};

/*
 * 32*64px text
 */
const uint8_t POKER_3_WIDTH = 32;
const uint8_t POKER_3_HEIGHT = 64;
const unsigned char POKER_3[256] = { /* 0X00,0X01,0X20,0X00,0X40,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE0,0X0F,0XFF,0XFF,0X00,0X01,0XFF,
0XFE,0X00,0X00,0XFF,0XF8,0X00,0X00,0X3F,0XF0,0X00,0X00,0X3F,0XF0,0X00,0X00,0X1F,
0XF0,0X3F,0XE0,0X1F,0XF0,0XFF,0XF0,0X0F,0XF3,0XFF,0XF8,0X0F,0XFF,0XFF,0XF8,0X0F,
0XFF,0XFF,0XF8,0X0F,0XFF,0XFF,0XFC,0X0F,0XFF,0XFF,0XFC,0X0F,0XFF,0XFF,0XFC,0X0F,
0XFF,0XFF,0XFC,0X0F,0XFF,0XFF,0XFC,0X0F,0XFF,0XFF,0XFC,0X0F,0XFF,0XFF,0XF8,0X0F,
0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0XF0,0X3F,0XFF,0XFF,0XE0,0X3F,
0XFF,0XFF,0X80,0X7F,0XFF,0XFC,0X01,0XFF,0XFE,0X00,0X03,0XFF,0XFE,0X00,0X03,0XFF,
0XFE,0X00,0X03,0XFF,0XFE,0X00,0X00,0X7F,0XFF,0X78,0X00,0X3F,0XFF,0XFF,0X80,0X1F,
0XFF,0XFF,0XF0,0X0F,0XFF,0XFF,0XF8,0X07,0XFF,0XFF,0XFC,0X07,0XFF,0XFF,0XFE,0X07,
0XFF,0XFF,0XFF,0X03,0XFF,0XFF,0XFF,0X01,0XFF,0XFF,0XFF,0X01,0XFF,0XFF,0XFF,0X01,
0XFF,0XFF,0XFF,0X81,0XFF,0XFF,0XFF,0X01,0XFF,0XFF,0XFF,0X01,0XFF,0XFF,0XFF,0X01,
0XFF,0XFF,0XFF,0X03,0XFF,0XFF,0XFF,0X07,0XFF,0XFF,0XFE,0X07,0XE7,0XFF,0XFC,0X07,
0XE1,0XFF,0XF8,0X0F,0XE0,0X3F,0XE0,0X0F,0XE0,0X00,0X00,0X1F,0XE0,0X00,0X00,0X3F,
0XE0,0X00,0X00,0X7F,0XFC,0X00,0X01,0XFF,0XFE,0X00,0X03,0XFF,0XFF,0XFD,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};

/*
 * 32*64px text
 */
const uint8_t POKER_4_WIDTH = 32;
const uint8_t POKER_4_HEIGHT = 64;
const unsigned char POKER_4[256] = { /* 0X00,0X01,0X20,0X00,0X40,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE7,0XFF,0XFF,0XFF,0X80,0XFF,
0XFF,0XFF,0X80,0XFF,0XFF,0XFF,0X00,0XFF,0XFF,0XFF,0X00,0XFF,0XFF,0XFE,0X00,0XFF,
0XFF,0XFE,0X00,0XFF,0XFF,0XFE,0X00,0XFF,0XFF,0XFC,0X00,0XFF,0XFF,0XF8,0X20,0XFF,
0XFF,0XF8,0X30,0XFF,0XFF,0XF8,0X70,0XFF,0XFF,0XF0,0X70,0XFF,0XFF,0XF0,0X70,0XFF,
0XFF,0XE0,0XF0,0XFF,0XFF,0XE1,0XF0,0XFF,0XFF,0XE1,0XF0,0XFF,0XFF,0XC1,0XF0,0XFF,
0XFF,0XC3,0XF0,0XFF,0XFF,0X83,0XF0,0XFF,0XFF,0X87,0XF0,0XFF,0XFF,0X07,0XF0,0XFF,
0XFF,0X07,0XF0,0XFF,0XFF,0X0F,0XF0,0XFF,0XFE,0X1F,0XF0,0XFF,0XFE,0X1F,0XF0,0XFF,
0XFC,0X1F,0XF0,0XFF,0XFC,0X3F,0XF0,0XFF,0XFC,0X3F,0XF0,0XFF,0XF8,0X7F,0XF0,0XFF,
0XF0,0X7F,0XF0,0XFF,0XF0,0X7F,0XF0,0XFF,0XF0,0XFF,0XF0,0XFF,0XE0,0XFF,0XF0,0XFF,
0XE0,0XFF,0XE0,0X7F,0XE0,0X00,0X00,0X27,0XE0,0X00,0X00,0X03,0XE0,0X00,0X00,0X03,
0XE0,0X00,0X00,0X03,0XE0,0X00,0X00,0X03,0XFF,0XFF,0XE0,0X3F,0XFF,0XFF,0XF0,0XFF,
0XFF,0XFF,0XF0,0XFF,0XFF,0XFF,0XF0,0XFF,0XFF,0XFF,0XF0,0XFF,0XFF,0XFF,0XF0,0XFF,
0XFF,0XFF,0XF0,0XFF,0XFF,0XFF,0XF0,0XFF,0XFF,0XFF,0XF0,0XFF,0XFF,0XFF,0XF0,0XFF,
0XFF,0XFF,0XF0,0XFF,0XFF,0XFF,0XF0,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};

/*
 * 32*64px text
 */
const uint8_t POKER_5_WIDTH = 32;
const uint8_t POKER_5_HEIGHT = 64;
const unsigned char POKER_5[256] = { /* 0X00,0X01,0X20,0X00,0X40,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X00,0X00,0X1F,
0XF8,0X00,0X00,0X0F,0XF8,0X00,0X00,0X0F,0XF8,0X00,0X00,0X0F,0XF8,0X00,0X00,0X1F,
0XF8,0X1F,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,
0XF8,0X1F,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,
0XF8,0X1F,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,
0XF8,0X1F,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,
0XF8,0X00,0X0F,0XFF,0XF8,0X00,0X00,0XFF,0XF8,0X00,0X00,0X7F,0XF8,0X00,0X00,0X3F,
0XF8,0X00,0X00,0X1F,0XFF,0XFF,0XC0,0X0F,0XFF,0XFF,0XF0,0X07,0XFF,0XFF,0XFC,0X07,
0XFF,0XFF,0XFC,0X03,0XFF,0XFF,0XFE,0X03,0XFF,0XFF,0XFE,0X03,0XFF,0XFF,0XFF,0X03,
0XFF,0XFF,0XFF,0X03,0XFF,0XFF,0XFF,0X83,0XFF,0XFF,0XFF,0X83,0XFF,0XFF,0XFF,0X83,
0XFF,0XFF,0XFF,0X83,0XFF,0XFF,0XFF,0X83,0XFF,0XFF,0XFF,0X83,0XFF,0XFF,0XFF,0X03,
0XFF,0XFF,0XFF,0X03,0XFF,0XFF,0XFE,0X03,0XFF,0XFF,0XFE,0X03,0XFF,0XFF,0XFC,0X07,
0XCF,0XFF,0XFC,0X07,0XC3,0XFF,0XF0,0X0F,0XC0,0XFF,0XC0,0X1F,0XC0,0X00,0X00,0X1F,
0XC0,0X00,0X00,0X7F,0XE0,0X00,0X00,0XFF,0XF0,0X00,0X01,0XFF,0XFC,0X00,0X07,0XFF,
0XFF,0XF8,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};

/*
 * 32*64px text
 */
const uint8_t POKER_6_WIDTH = 32;
const uint8_t POKER_6_HEIGHT = 64;
const unsigned char POKER_6[256] = { /* 0X00,0X01,0X20,0X00,0X40,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC3,0XFF,0XFF,0XFE,0X00,0X7F,
0XFF,0XF0,0X00,0X1F,0XFF,0XE0,0X00,0X0F,0XFF,0X80,0X00,0X0F,0XFF,0X80,0X00,0X0F,
0XFF,0X00,0XFF,0X0F,0XFE,0X03,0XFF,0XFF,0XFC,0X07,0XFF,0XFF,0XFC,0X0F,0XFF,0XFF,
0XF8,0X1F,0XFF,0XFF,0XF8,0X3F,0XFF,0XFF,0XF8,0X3F,0XFF,0XFF,0XF8,0X7F,0XFF,0XFF,
0XF0,0X7F,0XFF,0XFF,0XF0,0X7F,0XFF,0XFF,0XE0,0XFF,0XFF,0XFF,0XE0,0XFF,0XFF,0XFF,
0XE0,0XFF,0XFF,0XFF,0XE0,0XFF,0XFF,0XFF,0XE0,0XFF,0XFF,0XFF,0XE0,0XFF,0XBF,0XFF,
0XE0,0XFC,0X03,0XFF,0XC0,0XC0,0X00,0X7F,0XC0,0X00,0X00,0X3F,0XC0,0X00,0X00,0X1F,
0XC0,0X00,0X00,0X0F,0XC0,0X0F,0XF0,0X0F,0XC0,0X1F,0XF8,0X07,0XC0,0X7F,0XFE,0X07,
0XC0,0XFF,0XFE,0X07,0XC0,0XFF,0XFE,0X07,0XC0,0XFF,0XFF,0X07,0XC0,0XFF,0XFF,0X07,
0XC0,0XFF,0XFF,0X07,0XC0,0XFF,0XFF,0X07,0XC0,0XFF,0XFF,0X03,0XE0,0XFF,0XFF,0X03,
0XE0,0XFF,0XFF,0X07,0XE0,0XFF,0XFF,0X07,0XE0,0XFF,0XFF,0X07,0XE0,0XFF,0XFF,0X07,
0XE0,0X7F,0XFF,0X07,0XE0,0X7F,0XFE,0X07,0XF0,0X7F,0XFE,0X07,0XF0,0X3F,0XFC,0X0F,
0XF8,0X1F,0XFC,0X0F,0XF8,0X0F,0XF0,0X1F,0XFC,0X07,0XE0,0X1F,0XFC,0X00,0X00,0X3F,
0XFE,0X00,0X00,0X7F,0XFF,0X00,0X00,0XFF,0XFF,0X80,0X03,0XFF,0XFF,0XF0,0X0F,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};

/*
 * 32*64px text
 */
const uint8_t POKER_7_WIDTH = 32;
const uint8_t POKER_7_HEIGHT = 64;
const unsigned char POKER_7[256] = { /* 0X00,0X01,0X20,0X00,0X40,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE0,0X00,0X00,0X07,0XC0,0X00,0X00,0X07,
0XC0,0X00,0X00,0X07,0XC0,0X00,0X00,0X07,0XE0,0X00,0X00,0X07,0XF7,0XFF,0XFC,0X07,
0XFF,0XFF,0XFE,0X07,0XFF,0XFF,0XFE,0X07,0XFF,0XFF,0XFE,0X0F,0XFF,0XFF,0XFE,0X0F,
0XFF,0XFF,0XFC,0X0F,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0XF8,0X3F,
0XFF,0XFF,0XF8,0X3F,0XFF,0XFF,0XF0,0X3F,0XFF,0XFF,0XF0,0X3F,0XFF,0XFF,0XF0,0X7F,
0XFF,0XFF,0XE0,0X7F,0XFF,0XFF,0XE0,0X7F,0XFF,0XFF,0XE0,0XFF,0XFF,0XFF,0XC0,0XFF,
0XFF,0XFF,0XC1,0XFF,0XFF,0XFF,0X81,0XFF,0XFF,0XFF,0X81,0XFF,0XFF,0XFF,0X83,0XFF,
0XFF,0XFF,0X83,0XFF,0XFF,0XFF,0X03,0XFF,0XFF,0XFF,0X03,0XFF,0XFF,0XFF,0X07,0XFF,
0XFF,0XFE,0X07,0XFF,0XFF,0XFE,0X07,0XFF,0XFF,0XFC,0X0F,0XFF,0XFF,0XFC,0X0F,0XFF,
0XFF,0XFC,0X1F,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0XF8,0X3F,0XFF,
0XFF,0XF0,0X3F,0XFF,0XFF,0XF0,0X3F,0XFF,0XFF,0XF0,0X3F,0XFF,0XFF,0XF0,0X7F,0XFF,
0XFF,0XE0,0X7F,0XFF,0XFF,0XE0,0X7F,0XFF,0XFF,0XC0,0XFF,0XFF,0XFF,0XC0,0XFF,0XFF,
0XFF,0XC1,0XFF,0XFF,0XFF,0X81,0XFF,0XFF,0XFF,0X81,0XFF,0XFF,0XFF,0X83,0XFF,0XFF,
0XFF,0X03,0XFF,0XFF,0XFF,0X03,0XFF,0XFF,0XFF,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};

/*
 * 32*64px text
 */
const uint8_t POKER_8_WIDTH = 32;
const uint8_t POKER_8_HEIGHT = 64;
const unsigned char POKER_8[256] = { /* 0X00,0X01,0X20,0X00,0X40,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X07,0XFF,0XFF,0X80,0X01,0XFF,
0XFF,0X00,0X00,0XFF,0XFC,0X00,0X00,0X3F,0XFC,0X00,0X00,0X3F,0XF8,0X03,0XC0,0X1F,
0XF8,0X1F,0XF8,0X1F,0XF0,0X3F,0XF8,0X0F,0XF0,0X7F,0XFC,0X0F,0XE0,0X7F,0XFE,0X0F,
0XE0,0X7F,0XFE,0X0F,0XE0,0XFF,0XFE,0X07,0XE0,0XFF,0XFE,0X0F,0XE0,0XFF,0XFE,0X0F,
0XE0,0X7F,0XFE,0X0F,0XE0,0X7F,0XFE,0X0F,0XF0,0X7F,0XFC,0X0F,0XF0,0X3F,0XFC,0X1F,
0XF0,0X1F,0XF8,0X1F,0XF8,0X0F,0XF0,0X3F,0XFC,0X07,0XE0,0X7F,0XFC,0X03,0XC0,0X7F,
0XFE,0X00,0X00,0XFF,0XFF,0X00,0X03,0XFF,0XFF,0X80,0X03,0XFF,0XFF,0XC0,0X03,0XFF,
0XFF,0XE0,0X03,0XFF,0XFF,0XC0,0X01,0XFF,0XFF,0X00,0X00,0XFF,0XFE,0X01,0X00,0X7F,
0XFC,0X07,0XC0,0X3F,0XF8,0X0F,0XE0,0X1F,0XF8,0X1F,0XF8,0X0F,0XF0,0X3F,0XF8,0X0F,
0XE0,0X7F,0XFE,0X07,0XE0,0XFF,0XFE,0X07,0XE0,0XFF,0XFF,0X07,0XC0,0XFF,0XFF,0X03,
0XC0,0XFF,0XFF,0X03,0XC1,0XFF,0XFF,0X03,0XC1,0XFF,0XFF,0X03,0XC1,0XFF,0XFF,0X03,
0XC0,0XFF,0XFF,0X03,0XC0,0XFF,0XFF,0X07,0XC0,0XFF,0XFF,0X07,0XC0,0X7F,0XFE,0X07,
0XE0,0X3F,0XFC,0X07,0XE0,0X1F,0XF8,0X0F,0XF0,0X00,0X00,0X0F,0XF8,0X00,0X00,0X1F,
0XF8,0X00,0X00,0X3F,0XFE,0X00,0X00,0XFF,0XFF,0X00,0X01,0XFF,0XFF,0XFC,0X7F,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};

/*
 * 32*64px text
 */
const uint8_t POKER_9_WIDTH = 32;
const uint8_t POKER_9_HEIGHT = 64;
const unsigned char POKER_9[256] = { /* 0X00,0X01,0X20,0X00,0X40,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,0X07,0XFF,0XFF,0XC0,0X01,0XFF,
0XFF,0X80,0X00,0XFF,0XFE,0X00,0X00,0X7F,0XFE,0X00,0X00,0X3F,0XFC,0X03,0XC0,0X1F,
0XF8,0X0F,0XF8,0X1F,0XF8,0X1F,0XF8,0X0F,0XF0,0X3F,0XFC,0X0F,0XF0,0X3F,0XFE,0X0F,
0XF0,0X7F,0XFE,0X0F,0XF0,0X7F,0XFE,0X07,0XF0,0X7F,0XFE,0X07,0XE0,0X7F,0XFF,0X07,
0XE0,0X7F,0XFF,0X07,0XE0,0X7F,0XFF,0X07,0XE0,0XFF,0XFF,0X07,0XE0,0X7F,0XFF,0X87,
0XE0,0X7F,0XFF,0X87,0XE0,0X7F,0XFF,0X87,0XE0,0X7F,0XFF,0X83,0XF0,0X7F,0XFF,0X83,
0XF0,0X7F,0XFF,0X83,0XF0,0X3F,0XFF,0X03,0XF0,0X3F,0XFE,0X03,0XF0,0X1F,0XFC,0X03,
0XF8,0X07,0XF0,0X03,0XF8,0X00,0X00,0X03,0XFC,0X00,0X00,0X03,0XFE,0X00,0X00,0X07,
0XFF,0X80,0X03,0X07,0XFF,0XC0,0X07,0X87,0XFF,0XFF,0XFF,0X87,0XFF,0XFF,0XFF,0X07,
0XFF,0XFF,0XFF,0X07,0XFF,0XFF,0XFF,0X07,0XFF,0XFF,0XFF,0X07,0XFF,0XFF,0XFF,0X07,
0XFF,0XFF,0XFE,0X0F,0XFF,0XFF,0XFE,0X0F,0XFF,0XFF,0XFE,0X0F,0XFF,0XFF,0XFC,0X1F,
0XFF,0XFF,0XFC,0X1F,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0XF0,0X3F,0XFF,0XFF,0XE0,0X3F,
0XF3,0XFF,0XC0,0X7F,0XF0,0XFF,0X80,0XFF,0XF0,0X00,0X00,0XFF,0XF0,0X00,0X03,0XFF,
0XF0,0X00,0X03,0XFF,0XF8,0X00,0X0F,0XFF,0XFF,0X00,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};

/*
 * 32*64px text
 */
const uint8_t POKER_0_WIDTH = 32;
const uint8_t POKER_0_HEIGHT = 64;
const unsigned char POKER_0[256] = { /* 0X00,0X01,0X20,0X00,0X40,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X07,0XFF,0XFF,0XC0,0X01,0XFF,
0XFF,0X80,0X00,0XFF,0XFF,0X00,0X00,0X7F,0XFE,0X00,0X00,0X3F,0XFC,0X01,0XC0,0X1F,
0XFC,0X0F,0XF0,0X1F,0XF8,0X1F,0XF8,0X0F,0XF8,0X1F,0XFC,0X0F,0XF0,0X3F,0XFC,0X0F,
0XF0,0X3F,0XFE,0X07,0XF0,0X7F,0XFE,0X07,0XF0,0X7F,0XFE,0X07,0XE0,0X7F,0XFF,0X07,
0XE0,0XFF,0XFF,0X03,0XE0,0XFF,0XFF,0X03,0XE0,0XFF,0XFF,0X03,0XE0,0XFF,0XFF,0X03,
0XE0,0XFF,0XFF,0X03,0XE0,0XFF,0XFF,0X83,0XC0,0XFF,0XFF,0X83,0XC0,0XFF,0XFF,0X83,
0XC0,0XFF,0XFF,0X83,0XC0,0XFF,0XFF,0X83,0XC0,0XFF,0XFF,0X83,0XC0,0XFF,0XFF,0X83,
0XC0,0XFF,0XFF,0X83,0XC0,0XFF,0XFF,0X83,0XC0,0XFF,0XFF,0X83,0XC0,0XFF,0XFF,0X83,
0XC0,0XFF,0XFF,0X83,0XC0,0XFF,0XFF,0X83,0XE0,0XFF,0XFF,0X03,0XE0,0XFF,0XFF,0X03,
0XE0,0XFF,0XFF,0X03,0XE0,0XFF,0XFF,0X03,0XE0,0XFF,0XFF,0X07,0XE0,0X7F,0XFF,0X07,
0XE0,0X7F,0XFE,0X07,0XE0,0X7F,0XFE,0X07,0XF0,0X7F,0XFE,0X07,0XF0,0X3F,0XFE,0X0F,
0XF0,0X3F,0XFC,0X0F,0XF8,0X1F,0XFC,0X1F,0XF8,0X0F,0XF8,0X1F,0XFC,0X07,0XE0,0X3F,
0XFC,0X00,0X00,0X3F,0XFE,0X00,0X00,0X7F,0XFF,0X00,0X00,0XFF,0XFF,0X80,0X01,0XFF,
0XFF,0XC0,0X07,0XFF,0XFF,0XFC,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};

/*
 * 32*64px text
 */
const uint8_t POKER_J_WIDTH = 32;
const uint8_t POKER_J_HEIGHT = 64;
const unsigned char POKER_J[256] = { /* 0X00,0X01,0X20,0X00,0X40,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,0XC0,0X7F,
0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,
0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,
0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,
0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,
0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,
0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,
0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,
0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,
0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,
0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XC0,0X7F,0XFF,0XFF,0XC0,0X7F,
0XFF,0XFF,0XC0,0X7F,0XFF,0XFF,0X80,0X7F,0XFF,0XFF,0X00,0X7F,0XF0,0XFE,0X00,0XFF,
0XF0,0X00,0X00,0XFF,0XF0,0X00,0X01,0XFF,0XF0,0X00,0X01,0XFF,0XF0,0X00,0X07,0XFF,
0XF8,0X00,0X0F,0XFF,0XFF,0XC3,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};

/*
 * 32*64px text
 */
const uint8_t POKER_Q_WIDTH = 32;
const uint8_t POKER_Q_HEIGHT = 64;
const unsigned char POKER_Q[256] = { /* 0X00,0X01,0X20,0X00,0X40,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XE0,0X3F,0XFF,0XFF,0X80,0X0F,0XFF,0XFF,0X80,0X07,0XFF,
0XFF,0X00,0X03,0XFF,0XFE,0X00,0X03,0XFF,0XFC,0X1F,0XC1,0XFF,0XFC,0X1F,0XC1,0XFF,
0XF8,0X3F,0XE0,0XFF,0XF8,0X7F,0XF0,0XFF,0XF8,0X7F,0XF0,0XFF,0XF8,0XFF,0XF8,0X7F,
0XF0,0XFF,0XF8,0X7F,0XF0,0XFF,0XFC,0X7F,0XF1,0XFF,0XFC,0X7F,0XF1,0XFF,0XFC,0X7F,
0XF1,0XFF,0XFC,0X7F,0XE1,0XFF,0XFC,0X3F,0XE1,0XFF,0XFC,0X3F,0XE1,0XFF,0XFC,0X3F,
0XE1,0XFF,0XFC,0X3F,0XE3,0XFF,0XFC,0X3F,0XE3,0XFF,0XFE,0X3F,0XE3,0XFF,0XFE,0X3F,
0XE3,0XFF,0XFE,0X3F,0XE3,0XFF,0XFE,0X3F,0XE3,0XFF,0XFE,0X3F,0XE1,0XFF,0XFE,0X3F,
0XE1,0XFF,0XFC,0X3F,0XE1,0XFF,0XFC,0X3F,0XE1,0XFF,0XFC,0X3F,0XE1,0XFF,0XFC,0X3F,
0XE1,0XFF,0XFC,0X3F,0XE1,0XFF,0XFC,0X7F,0XF1,0XFF,0XFC,0X7F,0XF1,0XFF,0XFC,0X7F,
0XF1,0XFF,0XF8,0X7F,0XF0,0XFF,0XF8,0X7F,0XF0,0XFF,0XF8,0XFF,0XF8,0XFF,0XF0,0XFF,
0XF8,0X7F,0XF0,0XFF,0XF8,0X7F,0XE1,0XFF,0XF8,0X3F,0XC1,0XFF,0XFC,0X0F,0X81,0XFF,
0XFC,0X06,0X01,0XFF,0XFE,0X00,0X00,0XFF,0XFF,0X00,0X00,0X7F,0XFF,0X80,0X18,0X3F,
0XFF,0XC0,0X38,0X3F,0XFF,0XFF,0XFC,0X0F,0XFF,0XFF,0XFE,0X0F,0XFF,0XFF,0XFE,0X07,
0XFF,0XFF,0XFF,0X07,0XFF,0XFF,0XFF,0X87,0XFF,0XFF,0XFF,0XC7,0XFF,0XFF,0XFF,0XF7,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};

/*
 * 32*64px text
 */
const uint8_t POKER_K_WIDTH = 32;
const uint8_t POKER_K_HEIGHT = 64;
const unsigned char POKER_K[256] = { /* 0X00,0X01,0X20,0X00,0X40,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0X8F,
0XE0,0XFF,0XFF,0X07,0XE0,0XFF,0XFE,0X07,0XE0,0XFF,0XFC,0X07,0XE0,0XFF,0XF8,0X0F,
0XE0,0XFF,0XF8,0X1F,0XE0,0XFF,0XF0,0X3F,0XE0,0XFF,0XF0,0X3F,0XE0,0XFF,0XE0,0X7F,
0XE0,0XFF,0XC0,0X7F,0XE0,0XFF,0XC0,0XFF,0XE0,0XFF,0X81,0XFF,0XE0,0XFF,0X81,0XFF,
0XE0,0XFF,0X03,0XFF,0XE0,0XFE,0X07,0XFF,0XE0,0XFC,0X07,0XFF,0XE0,0XFC,0X0F,0XFF,
0XE0,0XF8,0X1F,0XFF,0XE0,0XF8,0X1F,0XFF,0XE0,0XF0,0X3F,0XFF,0XE0,0XE0,0X7F,0XFF,
0XE0,0XE0,0X7F,0XFF,0XE0,0XC0,0XFF,0XFF,0XE0,0XC1,0XFF,0XFF,0XE0,0X01,0XFF,0XFF,
0XE0,0X01,0XFF,0XFF,0XE0,0X01,0XFF,0XFF,0XE0,0X00,0XFF,0XFF,0XE0,0XC0,0XFF,0XFF,
0XE0,0XC0,0X7F,0XFF,0XE0,0XE0,0X3F,0XFF,0XE0,0XE0,0X3F,0XFF,0XE0,0XF0,0X1F,0XFF,
0XE0,0XF8,0X1F,0XFF,0XE0,0XF8,0X0F,0XFF,0XE0,0XFC,0X07,0XFF,0XE0,0XFC,0X07,0XFF,
0XE0,0XFE,0X03,0XFF,0XE0,0XFF,0X03,0XFF,0XE0,0XFF,0X81,0XFF,0XE0,0XFF,0X81,0XFF,
0XE0,0XFF,0X80,0XFF,0XE0,0XFF,0XC0,0X7F,0XE0,0XFF,0XC0,0X7F,0XE0,0XFF,0XE0,0X3F,
0XE0,0XFF,0XF0,0X3F,0XE0,0XFF,0XF8,0X1F,0XE0,0XFF,0XF8,0X0F,0XE0,0XFF,0XFC,0X0F,
0XE0,0XFF,0XFC,0X07,0XE0,0XFF,0XFE,0X07,0XE0,0XFF,0XFF,0X03,0XE0,0XFF,0XFF,0X03,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};


#ifdef epd1in54_V2_H
/*
 * Show builtin poker image and card value on display.
 * This function displays on waveshare 1.54 inch epaper display with 0 rotate angle
 * 
 * First character represent poker suit, alphabet C, D, H, S, and J.
 * Next two characters represent an integer from 1 to 13. Using J, Q, K for 11 to 13.
 */
void drawPoker_154in_deg0(const char* poker){
  char suit = poker[0];
  int value = atoi(&poker[1]);
  if(DEBUG_OUTPUT){
    Serial.printf("Suit: %c, value: %d\n", suit, value);
  }
  switch(suit){
    case 'C': // club
    case 'c':
      epd.SetFrameMemoryPartial(POKER_CLUB, POKER_IMAGE_CENTER_X-int(POKER_CLUB_WIDTH/2),POKER_IMAGE_CENTER_Y-int(POKER_CLUB_HEIGHT/2), POKER_CLUB_WIDTH,POKER_CLUB_HEIGHT);
      break;
    case 'D': // diamond
    case 'd':
      epd.SetFrameMemoryPartial(POKER_DIAMOND, POKER_IMAGE_CENTER_X-int(POKER_DIAMOND_WIDTH/2),POKER_IMAGE_CENTER_Y-int(POKER_DIAMOND_HEIGHT/2), POKER_DIAMOND_WIDTH,POKER_DIAMOND_HEIGHT);
      break;
    case 'H': // heart
    case 'h':
      epd.SetFrameMemoryPartial(POKER_HEART, POKER_IMAGE_CENTER_X-int(POKER_HEART_WIDTH/2),POKER_IMAGE_CENTER_Y-int(POKER_HEART_HEIGHT/2), POKER_HEART_WIDTH,POKER_HEART_HEIGHT);
      break;
    case 'S': // spade
    case 's':
      epd.SetFrameMemoryPartial(POKER_SPADE, POKER_IMAGE_CENTER_X-int(POKER_SPADE_WIDTH/2),POKER_IMAGE_CENTER_Y-int(POKER_SPADE_HEIGHT/2), POKER_SPADE_WIDTH,POKER_SPADE_HEIGHT);
      break;
    case 'J': // joker
    case 'j':
      epd.SetFrameMemoryPartial(POKER_JOKER, POKER_IMAGE_CENTER_X-int(POKER_JOKER_WIDTH/2),POKER_IMAGE_CENTER_Y-int(POKER_JOKER_HEIGHT/2), POKER_JOKER_WIDTH,POKER_JOKER_HEIGHT);
      break;
    default: // unknown image, using a simple black square instead.
      paint.SetWidth(64);
      paint.SetHeight(64);
      paint.Clear(COLORED);
      epd.SetFrameMemoryPartial(paint.GetImage(), POKER_IMAGE_CENTER_X-32, POKER_IMAGE_CENTER_Y-32, 64,64);
      break;
  }

  switch(value){
    case 1:
      epd.SetFrameMemoryPartial(POKER_A, POKER_TEXT_CENTER_X-int(POKER_A_WIDTH/2),POKER_TEXT_CENTER_Y-int(POKER_A_HEIGHT/2), POKER_A_WIDTH, POKER_A_HEIGHT);
      break;
    case 2:
      epd.SetFrameMemoryPartial(POKER_2, POKER_TEXT_CENTER_X-int(POKER_2_WIDTH/2),POKER_TEXT_CENTER_Y-int(POKER_2_HEIGHT/2), POKER_2_WIDTH, POKER_2_HEIGHT);
      break;
    case 3:
      epd.SetFrameMemoryPartial(POKER_3, POKER_TEXT_CENTER_X-int(POKER_3_WIDTH/2),POKER_TEXT_CENTER_Y-int(POKER_3_HEIGHT/2), POKER_3_WIDTH, POKER_3_HEIGHT);
      break;
    case 4:
      epd.SetFrameMemoryPartial(POKER_4, POKER_TEXT_CENTER_X-int(POKER_4_WIDTH/2),POKER_TEXT_CENTER_Y-int(POKER_4_HEIGHT/2), POKER_4_WIDTH, POKER_4_HEIGHT);
      break;
    case 5:
      epd.SetFrameMemoryPartial(POKER_5, POKER_TEXT_CENTER_X-int(POKER_5_WIDTH/2),POKER_TEXT_CENTER_Y-int(POKER_5_HEIGHT/2), POKER_5_WIDTH, POKER_5_HEIGHT);
      break;
    case 6:
      epd.SetFrameMemoryPartial(POKER_6, POKER_TEXT_CENTER_X-int(POKER_6_WIDTH/2),POKER_TEXT_CENTER_Y-int(POKER_6_HEIGHT/2), POKER_6_WIDTH, POKER_6_HEIGHT);
      break;
    case 7:
      epd.SetFrameMemoryPartial(POKER_7, POKER_TEXT_CENTER_X-int(POKER_7_WIDTH/2),POKER_TEXT_CENTER_Y-int(POKER_7_HEIGHT/2), POKER_7_WIDTH, POKER_7_HEIGHT);
      break;
    case 8:
      epd.SetFrameMemoryPartial(POKER_8, POKER_TEXT_CENTER_X-int(POKER_8_WIDTH/2),POKER_TEXT_CENTER_Y-int(POKER_8_HEIGHT/2), POKER_8_WIDTH, POKER_8_HEIGHT);
      break;
    case 9:
      epd.SetFrameMemoryPartial(POKER_9, POKER_TEXT_CENTER_X-int(POKER_9_WIDTH/2),POKER_TEXT_CENTER_Y-int(POKER_9_HEIGHT/2), POKER_9_WIDTH, POKER_9_HEIGHT);
      break;
    case 10:
      epd.SetFrameMemoryPartial(POKER_1, POKER_TEXT_CENTER_X-POKER_1_WIDTH,POKER_TEXT_CENTER_Y-int(POKER_1_HEIGHT/2), POKER_1_WIDTH, POKER_1_HEIGHT);
      epd.SetFrameMemoryPartial(POKER_0, POKER_TEXT_CENTER_X,POKER_TEXT_CENTER_Y-int(POKER_0_HEIGHT/2), POKER_0_WIDTH, POKER_0_HEIGHT);
      break;
    case 11:
      epd.SetFrameMemoryPartial(POKER_J, POKER_TEXT_CENTER_X-int(POKER_J_WIDTH/2),POKER_TEXT_CENTER_Y-int(POKER_J_HEIGHT/2), POKER_J_WIDTH, POKER_J_HEIGHT);
      break;
    case 12:
      epd.SetFrameMemoryPartial(POKER_Q, POKER_TEXT_CENTER_X-int(POKER_Q_WIDTH/2),POKER_TEXT_CENTER_Y-int(POKER_Q_HEIGHT/2), POKER_Q_WIDTH, POKER_Q_HEIGHT);
      break;
    case 13:
      epd.SetFrameMemoryPartial(POKER_K, POKER_TEXT_CENTER_X-int(POKER_K_WIDTH/2),POKER_TEXT_CENTER_Y-int(POKER_K_HEIGHT/2), POKER_K_WIDTH, POKER_K_HEIGHT);
      break;
    default: // out of spec, using 0.
      epd.SetFrameMemoryPartial(POKER_0, POKER_TEXT_CENTER_X-int(POKER_0_WIDTH/2),POKER_TEXT_CENTER_Y-int(POKER_0_HEIGHT/2), POKER_0_WIDTH, POKER_0_HEIGHT);
      break;
  }
  epd.DisplayPartFrame();
}
#endif // epd1in54_V2_H
#endif // _POKER_H_

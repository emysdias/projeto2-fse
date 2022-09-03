#ifndef LED_H_
#define LED_H_

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void lcd_print(float tr, float ti, int timer, int secons);
void ClrLcd(void);
void setup_lcd();

#endif
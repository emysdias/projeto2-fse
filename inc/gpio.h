#ifndef GPIO_H_
#define GPIO_H_

#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define PWM_MAX_RANGE 100
#define PWM_MIN_RANGE 0
#define RESISTOR_PIN 4
#define FAN_PIN 5

void setup_gpio();
void manage_gpio_devices(int intensity);
void enable_fan(int intensity);
void disable_fan();
void enable_resistor(int intensity);
void disable_resistor();
void disable_fan_and_resistor();

#endif
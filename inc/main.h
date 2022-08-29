#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include "uart.h"
#include "pid.h"
#include "gpio.h"

void shut_down_system();
void set_use_key_switch();
void set_potentiometer(int value);
void set_pid(int value);
void set_temperature_reference_input(int potentiometer_active, float new_temperature);
void set_new_hysteresis(float new_hysteresis);
void set_new_pid_constants(float new_Kp, float new_Ki, float new_Kd);

#endif
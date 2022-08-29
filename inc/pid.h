#ifndef PID_H_
#define PID_H_

#include <stdio.h>

void pid_configure_constants(double Kp_, double Ki_, double Kd_);
void pid_update_reference(float reference_);
double pid_control(double measurement_output);

#endif
#include "../inc/gpio.h"

void setup_gpio()
{
    wiringPiSetup();
    pinMode(FAN_PIN, OUTPUT);
    pinMode(RESISTOR_PIN, OUTPUT);
}

void enable_fan(int intensity)
{
    softPwmCreate(FAN_PIN, PWM_MIN_RANGE, PWM_MAX_RANGE);
    softPwmWrite(FAN_PIN, intensity);
}

void disable_fan()
{
    softPwmCreate(FAN_PIN, PWM_MIN_RANGE, PWM_MAX_RANGE);
    softPwmWrite(FAN_PIN, PWM_MIN_RANGE);
}

void enable_resistor(int intensity)
{
    softPwmCreate(RESISTOR_PIN, PWM_MIN_RANGE, PWM_MAX_RANGE);
    softPwmWrite(RESISTOR_PIN, intensity);
}

void disable_resistor()
{
    softPwmCreate(RESISTOR_PIN, PWM_MIN_RANGE, PWM_MAX_RANGE);
    softPwmWrite(RESISTOR_PIN, PWM_MIN_RANGE);
}

void disable_fan_and_resistor()
{
    disable_resistor();
    disable_fan();
}

void manage_gpio_devices(int intensity)
{
    if (intensity > 0)
    {
        enable_resistor(intensity);
        disable_fan();
    }
    else if (intensity < -40)
    {
        enable_fan((int)intensity * (-1));
        disable_resistor();
    }
    else
    {
        disable_fan_and_resistor();
    }
}
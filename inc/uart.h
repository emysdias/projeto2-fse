#ifndef UART_H_
#define UART_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "crc.h"

#define SERVER_CODE 0x01
#define REQUEST_CODE 0x23
#define SEND_CODE 0x16
#define REQUEST_DS18B20_TEMPERATURE 0xC1
#define REQUEST_POTENTIOMETER_TEMPERATURE 0xC2
#define REQUEST_KEY_STATE 0xC3
#define SEND_CONTROL_SIGNAL 0xD1
#define SEND_SYSTEM_STATE 0xD3
#define SEND_CONTROL_TEMPERATURE 0xD5
#define SEND_TIMER_VALUE 0xD6
#define REQ
#define DS18B20 0
#define POTENTIOMETER 1
#define KEY_STATE 2
#define CONTROL_SIGNAL 3
#define TIMER 4

int init_uart();
void write_uart_message_request(int uart, int code);
void write_uart_message_send(int uart, int control_signal);
void write_uart_message_send_geral(int uart, unsigned char code, int value);
void write_uart_message_send_char(int uart, unsigned char code, unsigned char value);
float read_uart_message_temperature(int uart);
int read_uart_message_key_state(int uart);
float potentiometer_temperature(int uart, float TR);
float DS18B20_temperature(int uart, float TI);
int get_key_state(int uart);
void send_control_signal(int uart, int control_signal);
void close_uart(int uart);

#endif
#ifndef UART_H
#define UART_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "stdio.h"
#include "driver/uart.h"

void uart_init();
void uart_send(const char * data );
void uart_send_int(int );
void uart_send_float(float ) ;

void uart_wait();


#define debug(text,...) \
    {\
    char string[100]; \
    sprintf(string, text, __VA_ARGS__);\
    uart_send(string);\
    }
#endif
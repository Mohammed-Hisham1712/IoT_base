#ifndef SERIAL_DEBUG_H
#define SERIAL_DEBUG_H

#include "driver/uart.h"

void serial_init();
void serial_send(const char *);
void serial_wait();

#endif

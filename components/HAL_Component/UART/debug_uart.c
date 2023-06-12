#include "debug_uart.h"
#include "types.h"

#define BUF_SIZE (1024)
void uart_init ()  
{
    uart_config_t uart_config = {
        .baud_rate = 74880,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_NUM_0, &uart_config);
    uart_driver_install(UART_NUM_0, BUF_SIZE * 1, 0, 0, NULL, 0);
}
void uart_send(const char * data  )
{
    int l_len = 0 ;

    while(data[l_len] != 0 )
    {
        l_len ++ ;
    }
    uart_write_bytes(UART_NUM_0, (const char *) data, l_len);
}
void uart_wait()
{
    uint8_t data[10];
    int len = 0 ;
    while ( len == 0 )
    {
        len = uart_read_bytes(UART_NUM_0, (uint8_t*)data, BUF_SIZE, 20 / portTICK_RATE_MS);
    }
}

void uart_send_int(int num)
{
    char str[20] ;
    sprintf(str, "%d\r\n", num);
    uart_send(str);
}
void uart_send_float ( float num) 
{
    char str[30] ;
    char *tmpSign = (num < 0) ? "-" : "";
    int tmpInt1 = num;                  // Get the integer (678).
    float tmpFrac = num - tmpInt1;      // Get fraction (0.0123).
    int tmpInt2 = tmpFrac * 10000;  // Turn into integer (123).
    sprintf(str,"%s%d.%04d\n", tmpSign, tmpInt1, tmpInt2);
    uart_send(str);
}




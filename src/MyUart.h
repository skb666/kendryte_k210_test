#ifndef _MYUART_H
#define _MYUART_H

#include "fpioa.h"
#include "uart.h"

#define PIN_UART_USB_RX (4)
#define PIN_UART_USB_TX (5)

#define UART_USB_NUM UART_DEVICE_1

#define FUNC_UART_USB_RX (FUNC_UART1_RX)
#define FUNC_UART_USB_TX (FUNC_UART1_TX)

void MyUart_hardware_init(void);
void MyUart_Init(void);

#endif

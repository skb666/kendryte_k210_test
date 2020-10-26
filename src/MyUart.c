#include "MyUart.h"

void MyUart_hardware_init(void) {
  fpioa_set_function(PIN_UART_USB_RX, FUNC_UART_USB_RX);
  fpioa_set_function(PIN_UART_USB_TX, FUNC_UART_USB_TX);
}

void MyUart_Init(void) {
  uart_init(UART_USB_NUM);
  uart_configure(UART_USB_NUM, 115200, UART_BITWIDTH_8BIT, UART_STOP_1,
                 UART_PARITY_NONE);
}

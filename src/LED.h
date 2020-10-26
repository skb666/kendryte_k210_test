#ifndef _LED_H
#define _LED_H

#include "fpioa.h"
#include "gpio.h"

#define PIN_LED_0 (0)
#define PIN_LED_1 (17)

#define LED0_GPIONUM (0)
#define LED1_GPIONUM (1)

#define FUNC_LED0 (FUNC_GPIO0)
#define FUNC_LED1 (FUNC_GPIO1)

typedef enum _led_enable_status {
  LED_ON,
  LED_OFF,
  LED_TOGGLE,
} led_enable_status;

void LED_hardware_init(uint8_t state);
void LED_Init(uint8_t state);
void LED_Control(uint8_t ledx, led_enable_status state);

#endif

#include "LED.h"

void LED_hardware_init(uint8_t state) {
  switch (state) {
    case 0:
      fpioa_set_function(PIN_LED_0, FUNC_LED0);
      break;
    case 1:
      fpioa_set_function(PIN_LED_1, FUNC_LED1);
      break;
    default:
      fpioa_set_function(PIN_LED_0, FUNC_LED0);
      fpioa_set_function(PIN_LED_1, FUNC_LED1);
      break;
  }
}

void LED_Init(uint8_t state) {
  switch (state) {
    case 0:
      gpio_set_drive_mode(LED0_GPIONUM, GPIO_DM_OUTPUT);
      LED_Control(LED0_GPIONUM, LED_OFF);
      break;
    case 1:
      gpio_set_drive_mode(LED1_GPIONUM, GPIO_DM_OUTPUT);
      LED_Control(LED1_GPIONUM, LED_OFF);
      break;
    default:
      gpio_set_drive_mode(LED0_GPIONUM, GPIO_DM_OUTPUT);
      gpio_set_drive_mode(LED1_GPIONUM, GPIO_DM_OUTPUT);
      LED_Control(LED0_GPIONUM, LED_OFF);
      LED_Control(LED1_GPIONUM, LED_OFF);
      break;
  }
}

void LED_Control(uint8_t ledx, led_enable_status state) {
  switch (state) {
    case LED_ON:
      gpio_set_pin(ledx, GPIO_PV_LOW);
      break;
    case LED_OFF:
      gpio_set_pin(ledx, GPIO_PV_HIGH);
      break;
    case LED_TOGGLE:
      gpio_set_pin(ledx, !gpio_get_pin(ledx));
  }
}

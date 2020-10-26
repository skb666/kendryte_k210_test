#include "KEY.h"

void KEY_hardware_init(void) { fpioa_set_function(PIN_KEY, FUNC_KEY); }

void KEYPAD_hardware_init(void) {
  fpioa_set_function(PIN_KEYPAD_LEFT, FUNC_KEYPAD_LEFT);
  fpioa_set_function(PIN_KEYPAD_MIDDLE, FUNC_KEYPAD_MIDDLE);
  fpioa_set_function(PIN_KEYPAD_RIGHT, FUNC_KEYPAD_RIGHT);
}

void KEY_Init(plic_irq_callback_t callback, void *ctx) {
  gpiohs_set_drive_mode(KEY_GPIONUM, GPIO_DM_INPUT_PULL_UP);
  gpiohs_set_pin_edge(KEY_GPIONUM, GPIO_PE_BOTH);
  gpiohs_irq_register(KEY_GPIONUM, 1, callback, ctx);
}

void KEYPAD_Init(void) {
  gpiohs_set_drive_mode(KEYPAD_LEFT_GPIONUM, GPIO_DM_INPUT_PULL_UP);
  gpiohs_set_drive_mode(KEYPAD_MIDDLE_GPIONUM, GPIO_DM_INPUT_PULL_UP);
  gpiohs_set_drive_mode(KEYPAD_RIGHT_GPIONUM, GPIO_DM_INPUT_PULL_UP);
}

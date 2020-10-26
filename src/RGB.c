#include "RGB.h"

void RGB_hardware_init(void) {
  fpioa_set_function(PIN_RGB_R, FUNC_RGB_R);
  fpioa_set_function(PIN_RGB_G, FUNC_RGB_G);
  fpioa_set_function(PIN_RGB_B, FUNC_RGB_B);
}

void RGB_Init(void) {
  gpiohs_set_drive_mode(RGB_R_GPIONUM, GPIO_DM_OUTPUT);
  gpiohs_set_drive_mode(RGB_G_GPIONUM, GPIO_DM_OUTPUT);
  gpiohs_set_drive_mode(RGB_B_GPIONUM, GPIO_DM_OUTPUT);

  RGB_OFF();
}

void RGB_OFF(void) {
  gpiohs_set_pin(RGB_R_GPIONUM, GPIO_PV_HIGH);
  gpiohs_set_pin(RGB_G_GPIONUM, GPIO_PV_HIGH);
  gpiohs_set_pin(RGB_B_GPIONUM, GPIO_PV_HIGH);
}

void RGB_Run(void) {
  static uint8_t state = 0;

  switch (state) {
    case 0:
      RGB_OFF();
      gpiohs_set_pin(RGB_R_GPIONUM, GPIO_PV_LOW);
      break;
    case 1:
      RGB_OFF();
      gpiohs_set_pin(RGB_G_GPIONUM, GPIO_PV_LOW);
      break;
    case 2:
      RGB_OFF();
      gpiohs_set_pin(RGB_B_GPIONUM, GPIO_PV_LOW);
      break;
    case 3:
      RGB_OFF();
      gpiohs_set_pin(RGB_R_GPIONUM, GPIO_PV_LOW);
      gpiohs_set_pin(RGB_G_GPIONUM, GPIO_PV_LOW);
      break;
    case 4:
      RGB_OFF();
      gpiohs_set_pin(RGB_R_GPIONUM, GPIO_PV_LOW);
      gpiohs_set_pin(RGB_B_GPIONUM, GPIO_PV_LOW);
      break;
    case 5:
      RGB_OFF();
      gpiohs_set_pin(RGB_G_GPIONUM, GPIO_PV_LOW);
      gpiohs_set_pin(RGB_B_GPIONUM, GPIO_PV_LOW);
      break;
    case 6:
      RGB_OFF();
      gpiohs_set_pin(RGB_R_GPIONUM, GPIO_PV_LOW);
      gpiohs_set_pin(RGB_G_GPIONUM, GPIO_PV_LOW);
      gpiohs_set_pin(RGB_B_GPIONUM, GPIO_PV_LOW);
      break;
  }

  state = (state + 1) % 7;
}

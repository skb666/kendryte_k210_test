#ifndef _RGB_H
#define _RGB_H

#include "fpioa.h"
#include "gpiohs.h"

#define PIN_RGB_R (6)
#define PIN_RGB_G (7)
#define PIN_RGB_B (8)

#define RGB_R_GPIONUM (0)
#define RGB_G_GPIONUM (1)
#define RGB_B_GPIONUM (2)

#define FUNC_RGB_R (FUNC_GPIOHS0)
#define FUNC_RGB_G (FUNC_GPIOHS1)
#define FUNC_RGB_B (FUNC_GPIOHS2)

void RGB_hardware_init(void);
void RGB_Init(void);
void RGB_OFF(void);
void RGB_Run(void);

#endif

#ifndef _KEY_H
#define _KEY_H

#include "fpioa.h"
#include "gpiohs.h"
#include "plic.h"

#define PIN_KEY (16)
#define PIN_KEYPAD_LEFT (1)
#define PIN_KEYPAD_MIDDLE (2)
#define PIN_KEYPAD_RIGHT (3)

#define KEY_GPIONUM (3)
#define KEYPAD_LEFT_GPIONUM (4)
#define KEYPAD_MIDDLE_GPIONUM (5)
#define KEYPAD_RIGHT_GPIONUM (6)

#define FUNC_KEY (FUNC_GPIOHS3)
#define FUNC_KEYPAD_LEFT (FUNC_GPIOHS4)
#define FUNC_KEYPAD_MIDDLE (FUNC_GPIOHS5)
#define FUNC_KEYPAD_RIGHT (FUNC_GPIOHS6)

#define KEY_IRQ (IRQN_GPIOHS3_INTERRUPT)

void KEY_hardware_init(void);
void KEYPAD_hardware_init(void);
void KEY_Init(plic_irq_callback_t callback, void *ctx);
void KEYPAD_Init(void);

#endif

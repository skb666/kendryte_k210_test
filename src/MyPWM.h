#ifndef _MYPWM_H
#define _MYPWM_H

#include "pwm.h"

typedef enum _pwm_enable_status {
  PWM_Disable,
  PWM_Enable,
} pwm_enable_status;

void MyPWM_Init(pwm_device_number_t pwm_device,
                pwm_channel_number_t pwm_channel, double frequency, double duty,
                pwm_enable_status pwm_status);

#endif

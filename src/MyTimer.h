#ifndef _MYTIMER_H
#define _MYTIMER_H

#include "timer.h"

typedef enum _timer_enable_status {
  Timer_Disable,
  Timer_Enable,
} timer_enable_status;

void MyTimer_Init(timer_device_number_t timer_device,
                  timer_channel_number_t timer_channel, uint32_t priority,
                  size_t ns, timer_callback_t callback, void *ctx,
                  timer_enable_status status);

#endif

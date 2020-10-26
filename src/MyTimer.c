#include "MyTimer.h"

void MyTimer_Init(timer_device_number_t timer_device,
                  timer_channel_number_t timer_channel, uint32_t priority,
                  size_t ns, timer_callback_t callback, void *ctx,
                  timer_enable_status status) {
  /* 定时器初始化 */
  timer_init(timer_device);
  /* 设置定时器超时时间，单位为ns*/
  timer_set_interval(timer_device, timer_channel, ns);
  /* 设置定时器中断回调 */
  timer_irq_register(timer_device, timer_channel, 0, priority, callback, &ctx);
  /* 使能定时器 */
  timer_set_enable(timer_device, timer_channel, status);
}

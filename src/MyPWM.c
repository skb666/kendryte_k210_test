#include "MyPWM.h"

void MyPWM_Init(pwm_device_number_t pwm_device,
                pwm_channel_number_t pwm_channel, double frequency, double duty,
                pwm_enable_status pwm_status) {
  /* 初始化PWM */
  pwm_init(pwm_device);
  /* 设置PWM频率为 frequency HZ，占空比为 duty 的方波 */
  pwm_set_frequency(pwm_device, pwm_channel, frequency, duty);
  /* 使能 PWM 输出 */
  pwm_set_enable(pwm_device, pwm_channel, pwm_status);
}

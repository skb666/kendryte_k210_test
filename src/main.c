#include "main.h"

#include <stdio.h>
#include <string.h>

#include "KEY.h"
#include "LED.h"
#include "MyPWM.h"
#include "MyTimer.h"
#include "MyUart.h"
#include "RGB.h"
#include "bsp.h"
#include "plic.h"
#include "sleep.h"
#include "sysctl.h"

uint8_t g_key_flag = 0;
uint8_t g_tim0_flag = 0;
uint8_t g_tim1_flag = 0;
corelock_t core_lock;
char txt_buff[50];

int core1_main(void *ctx);
void scan_keypad(void);
int key_irq_cb(void *ctx);
int timer0_timeout_cb(void *ctx);
int timer1_timeout_cb(void *ctx);

int main() {
  MyUart_hardware_init();
  MyUart_Init();

  /* 注册核心1，并启动核心1 */
  register_core1(core1_main, NULL);

  uint64_t core = current_coreid();
  corelock_lock(&core_lock);
  sprintf(txt_buff, "Core %ld say: Hello world\r\n", core);
  uart_send_data(UART_USB_NUM, txt_buff, strlen(txt_buff));
  corelock_unlock(&core_lock);

  char recv = 0;

  while (1) {
    /* 等待串口信息，并通过串口发送出去 */
    while (uart_receive_data(UART_USB_NUM, &recv, 1)) {
      uart_send_data(UART_USB_NUM, &recv, 1);
    }
  }

  return 0;
}

int core1_main(void *ctx) {
  LED_hardware_init(1);
  RGB_hardware_init();
  KEY_hardware_init();
  KEYPAD_hardware_init();
  fpioa_set_function(PIN_LED_0, FUNC_TIMER2_TOGGLE1);

  uint64_t core = current_coreid();
  corelock_lock(&core_lock);
  sprintf(txt_buff, "Core %ld say: Hello world\r\n", core);
  uart_send_data(UART_USB_NUM, txt_buff, strlen(txt_buff));
  corelock_unlock(&core_lock);

  /* 外部中断初始化 */
  plic_init();
  /* 使能全局中断 */
  sysctl_enable_irq();
  /* 使能gpio时钟 */
  gpio_init();

  LED_Init(1);
  RGB_Init();
  KEYPAD_Init();
  KEY_Init(key_irq_cb, &g_key_flag);
  /* 10ms */
  MyTimer_Init(TIMER_DEVICE_1, TIMER_CHANNEL_0, 2, 10 * 1e6, timer1_timeout_cb,
               &g_tim1_flag, Timer_Enable);
  /* 500ms */
  MyTimer_Init(TIMER_DEVICE_0, TIMER_CHANNEL_0, 1, 500 * 1e6, timer0_timeout_cb,
               &g_tim0_flag, Timer_Disable);
  /* freq: 200kHZ, duty: 50% */
  MyPWM_Init(PWM_DEVICE_2, PWM_CHANNEL_0, 200000, 0.5, PWM_Enable);

  while (1) {
    scan_keypad();
  }

  return 0;
}

void scan_keypad(void) {
  /* 读取keypad三个通道的状态 */
  gpio_pin_value_t state_keypad_left = gpiohs_get_pin(KEYPAD_LEFT_GPIONUM);
  gpio_pin_value_t state_keypad_middle = gpiohs_get_pin(KEYPAD_MIDDLE_GPIONUM);
  gpio_pin_value_t state_keypad_right = gpiohs_get_pin(KEYPAD_RIGHT_GPIONUM);

  /* 检测keypad是否向左滚动 */
  if (!state_keypad_left) {
    /* 延迟消抖10ms */
    msleep(10);
    /* 再次读keypad向左的IO口的状态 */
    state_keypad_left = gpiohs_get_pin(KEYPAD_LEFT_GPIONUM);
    if (!state_keypad_left) {
      /* 向左滚动，点亮红灯 */
      gpiohs_set_pin(RGB_R_GPIONUM, GPIO_PV_LOW);
    } else {
      /* 松开，红灯熄灭 */
      gpiohs_set_pin(RGB_R_GPIONUM, GPIO_PV_HIGH);
    }
  }
  /* 检测keypad是否被按下 */
  else if (!state_keypad_middle) {
    msleep(10);
    state_keypad_middle = gpiohs_get_pin(KEYPAD_MIDDLE_GPIONUM);
    if (!state_keypad_middle) {
      gpiohs_set_pin(RGB_G_GPIONUM, GPIO_PV_LOW);
    } else {
      gpiohs_set_pin(RGB_G_GPIONUM, GPIO_PV_HIGH);
    }
  }
  /* 检测keypad是否向右滚动 */
  else if (!state_keypad_right) {
    msleep(10);
    state_keypad_right = gpiohs_get_pin(KEYPAD_RIGHT_GPIONUM);
    if (!state_keypad_right) {
      gpiohs_set_pin(RGB_B_GPIONUM, GPIO_PV_LOW);
    } else {
      gpiohs_set_pin(RGB_B_GPIONUM, GPIO_PV_HIGH);
    }
  }
}

int key_irq_cb(void *ctx) {
  gpio_pin_value_t key_state = gpiohs_get_pin(KEY_GPIONUM);
  uint8_t *tmp = (uint8_t *)(ctx);

  LED_Control(LED1_GPIONUM, LED_TOGGLE);

  if (corelock_trylock(&core_lock) == 0) {
    sprintf(txt_buff, "IRQ The PIN is %d\n", key_state);
    uart_send_data(UART_USB_NUM, txt_buff, strlen(txt_buff));
    sprintf(txt_buff, "count is %d\n", *tmp);
    uart_send_data(UART_USB_NUM, txt_buff, strlen(txt_buff));
    *tmp = (*tmp + 1) % 2;
    corelock_unlock(&core_lock);
  }

  if (!key_state) {
    timer_set_enable(TIMER_DEVICE_0, TIMER_CHANNEL_0, Timer_Enable);
  } else {
    timer_set_enable(TIMER_DEVICE_0, TIMER_CHANNEL_0, Timer_Disable);
    RGB_OFF();
  }

  return 0;
}

int timer0_timeout_cb(void *ctx) {
  // uint8_t *tmp = (uint8_t *)(ctx);

  RGB_Run();

  return 0;
}

int timer1_timeout_cb(void *ctx) {
  static double duty_cycle = 0.01;
  /* 0为渐增，1为渐减 */
  static int flag = 0;

  /* 传入cycle的不同值，调节PWM的占用比，也就是调节灯的亮度 */
  pwm_set_frequency(PWM_DEVICE_2, PWM_CHANNEL_0, 200000, duty_cycle);

  /* 修改cycle的值，让其在区间（0,1）内渐增和渐减 */
  flag ? (duty_cycle -= 0.01) : (duty_cycle += 0.01);

  if (duty_cycle > 1.0) {
    duty_cycle = 1.0;
    flag = 1;
  } else if (duty_cycle < 0.0) {
    duty_cycle = 0.0;
    flag = 0;
  }

  return 0;
}

#pragma once

#include <X_general.h>

extern volatile uint32_t  uwTick;


typedef enum
{
  X_OK       = 0x00U,
  X_ERROR    = 0x01U,
  X_BUSY     = 0x02U,
  X_TIMEOUT  = 0x03U
} X_StatusTypeDef;

#define HSE_STARTUP_TIMEOUT    ((uint16_t)0x0500)   /*!< Time out for HSE start up */

// CORTEX Preemption Priority Group
#define NVIC_PRIORITYGROUP_0__0_pre_4_sub               0x7U
#define NVIC_PRIORITYGROUP_1__1_pre_3_sub               0x6U
#define NVIC_PRIORITYGROUP_2__2_pre_2_sub               0x5U
#define NVIC_PRIORITYGROUP_3__3_pre_1_sub               0x4U
#define NVIC_PRIORITYGROUP_4__4_pre_0_sub               0x3U

// GPIO Pins Mask definitions
#define GPIO_PIN_0_MSK                                  0x1U
#define GPIO_PIN_1_MSK                                  0x2U
#define GPIO_PIN_2_MSK                                  0x4U
#define GPIO_PIN_3_MSK                                  0x8U
#define GPIO_PIN_4_MSK                                  0x10U
#define GPIO_PIN_5_MSK                                  0x20U
#define GPIO_PIN_6_MSK                                  0x40U
#define GPIO_PIN_7_MSK                                  0x80U
#define GPIO_PIN_8_MSK                                  0x100U
#define GPIO_PIN_9_MSK                                  0x200U
#define GPIO_PIN_10_MSK                                 0x400U
#define GPIO_PIN_11_MSK                                 0x800U
#define GPIO_PIN_12_MSK                                 0x1000U
#define GPIO_PIN_13_MSK                                 0x2000U
#define GPIO_PIN_14_MSK                                 0x4000U
#define GPIO_PIN_15_MSK                                 0x8000U
#define GPIO_PIN_All_MSK                                0xFFFFU

// GPIO Pins Number definitions
#define GPIO_PIN_0_NUM                                  0x0U
#define GPIO_PIN_1_NUM                                  0x1U
#define GPIO_PIN_2_NUM                                  0x2U
#define GPIO_PIN_3_NUM                                  0x3U
#define GPIO_PIN_4_NUM                                  0x4U
#define GPIO_PIN_5_NUM                                  0x5U
#define GPIO_PIN_6_NUM                                  0x6U
#define GPIO_PIN_7_NUM                                  0x7U
#define GPIO_PIN_8_NUM                                  0x8U
#define GPIO_PIN_9_NUM                                  0x9U
#define GPIO_PIN_10_NUM                                 0xAU
#define GPIO_PIN_11_NUM                                 0xBU
#define GPIO_PIN_12_NUM                                 0xCU
#define GPIO_PIN_13_NUM                                 0xDU
#define GPIO_PIN_14_NUM                                 0xEU
#define GPIO_PIN_15_NUM                                 0xFU

void X_System_Init(void);
void X_Delay_ms(uint32_t Delay);
void X_Clock_Init_72MHz (void);
void X_Clock_Init_8MHz (void);
void X_RCC_MCO (void);
int _write(int file, char *ptr,int len);
void delay(unsigned int time);



#include "X_general.h"
#include "X_stm32f1xx_it_funcs.h"


EXTI_CallBack_Typedef  X_CallBack_EXTI;
TIM1_CallBack_Typedef  X_CallBack_TIM1;
TIM2_CallBack_Typedef  X_CallBack_TIM2;
TIM2_CallBack_Typedef  X_CallBack_TIM3;
TIM2_CallBack_Typedef  X_CallBack_TIM4;
DMA1_CallBack_Typedef  X_CallBack_DMA1_Ch1;
DMA1_CallBack_Typedef  X_CallBack_DMA1_Ch2;
DMA1_CallBack_Typedef  X_CallBack_DMA1_Ch3;
DMA1_CallBack_Typedef  X_CallBack_DMA1_Ch4;
DMA1_CallBack_Typedef  X_CallBack_DMA1_Ch5;
DMA1_CallBack_Typedef  X_CallBack_DMA1_Ch6;
DMA1_CallBack_Typedef  X_CallBack_DMA1_Ch7;
ADC_CallBack_Typedef   X_CallBack_ADC1;
ADC_CallBack_Typedef   X_CallBack_ADC2;
RTC_CallBack_Typedef   X_CallBack_RTC;
USART_CallBack_Typedef X_CallBack_USART1;
USART_CallBack_Typedef X_CallBack_USART2;
USART_CallBack_Typedef X_CallBack_USART3;
ALARM_CallBack_Typedef X_CallBack_ALARM;

//IRQ_Handler
void NMI_Handler               (void){while(1){}}
void HardFault_Handler         (void){while(1){}}
void MemManage_Handler         (void){while(1){}}
void BusFault_Handler          (void){while(1){}}
void UsageFault_Handler        (void){while(1){}}
void SVC_Handler               (void){}
void DebugMon_Handler          (void){}
void PendSV_Handler            (void){}
void SysTick_Handler           (void){uwTick+=1;}
void WWDG_IRQHandler           (void){}
void PVD_IRQHandler            (void){}
void TAMPER_IRQHandler         (void){}
void RTC_IRQHandler            (void){X_RTC_IRQHandler();}
void FLASH_IRQHandler          (void){}
void RCC_IRQHandler            (void){}
void EXTI0_IRQHandler          (void){X_EXTI0_IRQHandler();}
void EXTI1_IRQHandler          (void){X_EXTI1_IRQHandler();}
void EXTI2_IRQHandler          (void){X_EXTI2_IRQHandler();}
void EXTI3_IRQHandler          (void){X_EXTI3_IRQHandler();}
void EXTI4_IRQHandler          (void){X_EXTI4_IRQHandler();}
void DMA1_Channel1_IRQHandler  (void){X_DMA1_Channel1_IRQHandler();}
void DMA1_Channel2_IRQHandler  (void){X_DMA1_Channel2_IRQHandler();}
void DMA1_Channel3_IRQHandler  (void){X_DMA1_Channel3_IRQHandler();}
void DMA1_Channel4_IRQHandler  (void){X_DMA1_Channel4_IRQHandler();}
void DMA1_Channel5_IRQHandler  (void){X_DMA1_Channel5_IRQHandler();}
void DMA1_Channel6_IRQHandler  (void){X_DMA1_Channel6_IRQHandler();}
void DMA1_Channel7_IRQHandler  (void){X_DMA1_Channel7_IRQHandler();}
void ADC1_2_IRQHandler         (void){
	X_ADC1_IRQHandler();
	X_ADC2_IRQHandler();
}
void USB_HP_CAN1_TX_IRQHandler (void){}
void USB_LP_CAN1_RX0_IRQHandler(void){}
void CAN1_RX1_IRQHandler       (void){}
void CAN1_SCE_IRQHandler       (void){}
void EXTI9_5_IRQHandler        (void){X_EXTI9_5_IRQHandler();}
void TIM1_BRK_IRQHandler       (void){X_TIM1_BRK_IRQHandler    ();}
void TIM1_UP_IRQHandler        (void){X_TIM1_UP_IRQHandler     ();}
void TIM1_TRG_COM_IRQHandler   (void){X_TIM1_TRG_COM_IRQHandler();}
void TIM1_CC_IRQHandler        (void){X_TIM1_CC_IRQHandler     ();}
void TIM2_IRQHandler           (void){X_TIM2_IRQHandler();}
void TIM3_IRQHandler           (void){X_TIM3_IRQHandler();}
void TIM4_IRQHandler           (void){X_TIM4_IRQHandler();}
void I2C1_EV_IRQHandler        (void){}
void I2C1_ER_IRQHandler        (void){}
void I2C2_EV_IRQHandler        (void){}
void I2C2_ER_IRQHandler        (void){}
void SPI1_IRQHandler           (void){}
void SPI2_IRQHandler           (void){}
void USART1_IRQHandler         (void){X_USART1_IRQHandler();}
void USART2_IRQHandler         (void){X_USART2_IRQHandler();}
void USART3_IRQHandler         (void){X_USART3_IRQHandler();}
void EXTI15_10_IRQHandler      (void){X_EXTI15_10_IRQHandler();}
void RTC_Alarm_IRQHandler      (void){X_RTC_Alarm_IRQHandler();}
void USBWakeUp_IRQHandler      (void){}

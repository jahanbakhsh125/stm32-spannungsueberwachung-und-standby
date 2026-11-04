#pragma once



/******************************************************************************
 ******     Function Pointer Types for CallBack Function
******************************************************************************/

 // Typedef for RTC interrupt function pointers
 typedef struct{
 	 void (*OW) (void);
 	 void (*ALR)(void);
 	 void (*SEC)(void);
 } RTC_CallBack_Typedef;

 typedef void (*ALARM_CallBack_Typedef)(void);

 // Typedef for TIM2to4 interrupt function pointers
 typedef struct{
 	void (*UP)  (void);
 	void (*CC1) (void);
 	void (*CC2) (void);
 	void (*CC3) (void);
 	void (*CC4) (void);
 	void (*TRG) (void);
 } TIM2_CallBack_Typedef;

 // Typedef for TIM1 interrupt function pointers
 typedef struct{
 	void (*UP)  (void);
 	void (*CC1) (void);
 	void (*CC2) (void);
 	void (*CC3) (void);
 	void (*CC4) (void);
 	void (*COM) (void);
 	void (*TRG) (void);
 	void (*BRK) (void);
 } TIM1_CallBack_Typedef;


 // Typedef for DMA interrupt function pointers
 typedef struct{
 	void (*HT)  (void);
 	void (*TC)  (void);
 	void (*TE)  (void);
 } DMA1_CallBack_Typedef;



 // Typedef for ADC interrupt function pointers
 typedef struct{
 	void (*EOC) (void);
 	void (*JEOC)(void);
 	void (*AWD) (void);
 } ADC_CallBack_Typedef;



 // Typedef for EXTI interrupt function pointers
 typedef struct{
 	void (*L0) (void);
 	void (*L1) (void);
 	void (*L2) (void);
 	void (*L3) (void);
 	void (*L4) (void);
 	void (*L5) (void);
 	void (*L6) (void);
 	void (*L7) (void);
 	void (*L8) (void);
 	void (*L9) (void);
 	void (*L10)(void);
 	void (*L11)(void);
 	void (*L12)(void);
 	void (*L13)(void);
 	void (*L14)(void);
 	void (*L15)(void);
 } EXTI_CallBack_Typedef;


 // Typedef for USART interrupt function pointers
 typedef struct{
 	void (*TXE) (void);
 	void (*CTS) (void);
 	void (*TC)  (void);
 	void (*RXNE)(void);
 	void (*ORE) (void);
 	void (*IDLE)(void);
 	void (*PE)  (void);
 	void (*LBD) (void);
 	void (*E)   (void);
 	void (*FE)  (void);
 } USART_CallBack_Typedef;

 /******************************************************************************
  ******     extern definition of Function Pointers for CallBack Functions
 ******************************************************************************/

 extern EXTI_CallBack_Typedef  X_CallBack_EXTI;
 extern TIM1_CallBack_Typedef  X_CallBack_TIM1;
 extern TIM2_CallBack_Typedef  X_CallBack_TIM2;
 extern TIM2_CallBack_Typedef  X_CallBack_TIM3;
 extern TIM2_CallBack_Typedef  X_CallBack_TIM4;
 extern DMA1_CallBack_Typedef   X_CallBack_DMA1_Ch1;
 extern DMA1_CallBack_Typedef   X_CallBack_DMA1_Ch2;
 extern DMA1_CallBack_Typedef   X_CallBack_DMA1_Ch3;
 extern DMA1_CallBack_Typedef   X_CallBack_DMA1_Ch4;
 extern DMA1_CallBack_Typedef   X_CallBack_DMA1_Ch5;
 extern DMA1_CallBack_Typedef   X_CallBack_DMA1_Ch6;
 extern DMA1_CallBack_Typedef   X_CallBack_DMA1_Ch7;
 extern ADC_CallBack_Typedef   X_CallBack_ADC1;
 extern ADC_CallBack_Typedef   X_CallBack_ADC2;
 extern USART_CallBack_Typedef X_CallBack_USART1;
 extern USART_CallBack_Typedef X_CallBack_USART2;
 extern USART_CallBack_Typedef X_CallBack_USART3;
 extern RTC_CallBack_Typedef   X_CallBack_RTC;
 extern ALARM_CallBack_Typedef X_CallBack_ALARM;


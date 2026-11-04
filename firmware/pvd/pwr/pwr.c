#include "pwr.h"

#define __C_LED_OFF	GPIOC->BSRR = GPIO_BSRR_BS13
#define __C_LED_ON	GPIOC->BSRR = GPIO_BSRR_BR13

#define __B_LED_ON	GPIOB->BSRR = GPIO_BSRR_BS13
#define __B_LED_OFF	GPIOB->BSRR = GPIO_BSRR_BR13

void mypvd(void){
	if( PWR->CSR & PWR_CSR_PVDO ){
		__B_LED_ON;
	}else{
		__C_LED_ON;
	}


}

void PVD_Init(void){

	RCC->APB1ENR |= RCC_APB1ENR_PWREN;

	PWR->CR |= PWR_CR_PVDE;
	PWR->CR |= PWR_CR_PLS;

	EXTI->FTSR |= EXTI_FTSR_FT16;
	EXTI->RTSR |= EXTI_RTSR_RT16;

	EXTI->IMR |= EXTI_IMR_MR16;

	X_CallBack_PVD = mypvd;

	uint32_t PG=NVIC_GetPriorityGrouping();
	NVIC_SetPriority(PVD_IRQn,NVIC_EncodePriority(PG, 10, 0));
	EXTI->PR = EXTI_PR_PR16;
	NVIC_EnableIRQ(PVD_IRQn);



}











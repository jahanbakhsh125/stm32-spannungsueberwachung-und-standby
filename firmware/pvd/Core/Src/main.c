#include <X_general.h>
#include "rtc.h"
#include "lcd.h"
#include "usart.h"
#include "stdio.h"
#include "string.h"
#include "pwr.h"

#define __C_LED_OFF	GPIOC->BSRR = GPIO_BSRR_BS13
#define __C_LED_ON	GPIOC->BSRR = GPIO_BSRR_BR13

#define __B_LED_ON	GPIOB->BSRR = GPIO_BSRR_BS13
#define __B_LED_OFF	GPIOB->BSRR = GPIO_BSRR_BR13

int main(void){

	X_Clock_Init_72MHz();
	X_System_Init();

	//pc13
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH &= ~(GPIO_CRH_MODE13|GPIO_CRH_CNF13);
	GPIOC->CRH |= GPIO_CRH_MODE13_1;

	//PB13
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	GPIOB->CRH &= ~(GPIO_CRH_MODE13|GPIO_CRH_CNF13);
	GPIOB->CRH |= GPIO_CRH_MODE13_1;

	__C_LED_OFF;

	PVD_Init();




	/*
	lcd_init();
	usart_init();
*/


	while(1){





	}
}

void PB2_init(void){
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	GPIOB->CRL &= ~(GPIO_CRL_MODE2|GPIO_CRL_CNF2);
	GPIOB->CRL |= GPIO_CRL_CNF2_0;
}

void X_RTC_init(void){
	RCC->APB1ENR |= (RCC_APB1ENR_BKPEN|RCC_APB1ENR_PWREN);

	PWR->CR |= PWR_CR_DBP;


	if(GPIOB->IDR & GPIO_IDR_IDR2){

		RTC_Init();

		labview_time();


	}

	RTC_Init2();

	RTC_Alarm_init();
}

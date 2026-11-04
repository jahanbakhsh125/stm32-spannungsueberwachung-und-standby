#include "lcd.h"

#define __SEND_DATA GPIOA->BSRR = GPIO_BSRR_BS9
#define __SEND_COMMAND GPIOA->BSRR = GPIO_BSRR_BR9

uint32_t byte2write[32];

void lcd_dma_init(void){

	RCC->AHBENR |= RCC_AHBENR_DMA1EN;

	DMA1_Channel3->CPAR = (uint32_t)&GPIOA->BSRR;

	DMA1_Channel3->CMAR = (uint32_t)byte2write;


	DMA1_Channel3->CCR = 0;

	DMA1_Channel3->CCR |= (DMA_CCR_PSIZE_1|DMA_CCR_MSIZE_1|DMA_CCR_DIR|DMA_CCR_MINC);









}

void lcd_peripheral_init(void){

	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

	//data pin
	GPIOA->CRL = 0x22222222;

	GPIOA->CRH &= ~( GPIO_CRH_CNF9 | GPIO_CRH_MODE9 );
	GPIOA->CRH |= GPIO_CRH_MODE9_1;

	GPIOA->CRH &= ~(GPIO_CRH_MODE8|GPIO_CRH_CNF8);
	GPIOA->CRH |= GPIO_CRH_MODE8_1|GPIO_CRH_CNF8_1;

	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

	TIM1->CR1 &= ~(TIM_CR1_CKD|TIM_CR1_CMS|TIM_CR1_DIR);
	TIM1->CR1 |= TIM_CR1_OPM;

	TIM1->ARR = (uint16_t)59;
	TIM1->PSC = (uint16_t)71;

	TIM1->CCR1 = (uint16_t)15;
	TIM1->CCR2 = (uint16_t)3;

	TIM1->CCMR1 |= TIM_CCMR1_CC1S;
	TIM1->CCMR1 |= TIM_CCMR1_OC1PE;
	TIM1->CCMR1 &= ~TIM_CCMR1_CC1S;

	TIM1->CCMR1 &= ~TIM_CCMR1_CC2S;

	TIM1->CCMR1 &= ~TIM_CCMR1_OC1M;
	TIM1->CCMR1 |= ( TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 );

	TIM1->CCMR1 &= ~TIM_CCMR1_OC2M;

	TIM1->CCER &= ~TIM_CCER_CC1P;

	TIM1->CCER |= ( TIM_CCER_CC1E | TIM_CCER_CC2E);

	TIM1->BDTR |= TIM_BDTR_MOE;

	TIM1->DIER |= TIM_DIER_CC2DE;

	lcd_dma_init();


}


void data_prepare(uint8_t * byte,uint8_t size){

	for(uint8_t i=0;i<size;i++)
		byte2write[i]= (uint32_t)byte[i] | (~((uint32_t)byte[i]<<16) & 0xFF0000);


}

void lcd_print(uint8_t * string,uint8_t size){

	while(TIM1->CR1 & TIM_CR1_CEN);

	DMA1_Channel3->CCR &= ~DMA_CCR_EN;
	DMA1_Channel3->CNDTR = size;

	__SEND_DATA;

	data_prepare(string, size);

	TIM1->RCR = size-1;

	TIM1->DIER &= ~TIM_DIER_CC2IE;
	TIM1->EGR = TIM_EGR_UG;
	TIM1->SR = ~TIM_SR_CC2IF;
	TIM1->DIER |= TIM_DIER_CC2IE;



	DMA1_Channel3->CCR |= DMA_CCR_EN;
	TIM1->CR1 |= TIM_CR1_CEN;
}


void lcd_command(uint8_t command){

	while(TIM1->CR1 & TIM_CR1_CEN);

	DMA1_Channel3->CCR &= ~DMA_CCR_EN;
	DMA1_Channel3->CNDTR = 1;

	__SEND_COMMAND;

	byte2write[0]= (uint32_t)command | (~((uint32_t)command<<16) & 0xFF0000);

	TIM1->RCR = 0;

	TIM1->DIER &= ~TIM_DIER_CC2IE;
	TIM1->EGR = TIM_EGR_UG;
	TIM1->SR = ~TIM_SR_CC2IF;
	TIM1->DIER |= TIM_DIER_CC2IE;

	DMA1_Channel3->CCR |= DMA_CCR_EN;
	TIM1->CR1 |= TIM_CR1_CEN;
}


void lcd_init(void){
	lcd_peripheral_init();
	X_Delay_ms(20);
	lcd_command(0x30);
	X_Delay_ms(5);
	lcd_command(0x30);
	X_Delay_ms(5);
	lcd_command(0x30);
	X_Delay_ms(1);

	lcd_command(LCD_FUNCTIONSET|LCD_FUNCTION_N|LCD_FUNCTION_DL);
	lcd_command(LCD_DISPLAYCONTROL|LCD_DISPLAY_D);
	lcd_command(LCD_CLEARDISPLAY);
	X_Delay_ms(5);

}

void lcd_Set_cursor(uint8_t row,uint8_t col){

	switch(row){
	case 1:
		lcd_command((col-1)|0x80);
		break;

	case 2:
		lcd_command((col-1)|0x80|0x40);
		break;
	}



}







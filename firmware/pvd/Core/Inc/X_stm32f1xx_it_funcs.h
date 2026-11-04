#pragma once


#undef NULL  /* others (e.g. <stdio.h>) also define */
#define NULL 0
#define __CALL( CallBack_ptr ) ((CallBack_ptr != NULL ) ? CallBack_ptr() : (void)0U)


static inline void X_PVD_IRQHandler(void){
	EXTI->PR = EXTI_PR_PR16;
	__CALL(X_CallBack_PVD);

}

static inline void X_RTC_Alarm_IRQHandler(void){
	EXTI->PR = EXTI_PR_PR17;
	__CALL(X_CallBack_ALARM);

}

static inline void X_RTC_IRQHandler(void){

	if( ( RTC->CRL & RTC_CRL_SECF) && ( RTC->CRH & RTC_CRH_SECIE )){
		while(!(RTC->CRL & RTC_CRL_RTOFF));
		RTC->CRL = ~RTC_CRL_SECF;
		__CALL(X_CallBack_RTC.SEC);
	}


	if( ( RTC->CRL & RTC_CRL_OWF) && ( RTC->CRH & RTC_CRH_OWIE )){
		while(!(RTC->CRL & RTC_CRL_RTOFF));
		RTC->CRL = ~RTC_CRL_OWF;
		__CALL(X_CallBack_RTC.OW);
	}

}


static inline void X_EXTI15_10_IRQHandler(void){
 	  if(EXTI->PR & GPIO_PIN_10_MSK){
 		  EXTI->PR = GPIO_PIN_10_MSK;
 		  __CALL(X_CallBack_EXTI.L10);}

 	  if(EXTI->PR & GPIO_PIN_11_MSK){
 		  EXTI->PR = GPIO_PIN_11_MSK;
 		  __CALL(X_CallBack_EXTI.L11);}

 	  if(EXTI->PR & GPIO_PIN_12_MSK){
 		  EXTI->PR = GPIO_PIN_12_MSK;
 		  __CALL(X_CallBack_EXTI.L12);}

 	  if(EXTI->PR & GPIO_PIN_13_MSK){
 		  EXTI->PR = GPIO_PIN_13_MSK;
 		  __CALL(X_CallBack_EXTI.L13);}

 	  if(EXTI->PR & GPIO_PIN_14_MSK){
 		  EXTI->PR = GPIO_PIN_14_MSK;
 		  __CALL(X_CallBack_EXTI.L14);}

 	  if(EXTI->PR & GPIO_PIN_15_MSK){
 		  EXTI->PR = GPIO_PIN_15_MSK;
 		  __CALL(X_CallBack_EXTI.L15);}
}

static inline void X_EXTI9_5_IRQHandler(void){
 	  if(EXTI->PR & GPIO_PIN_5_MSK){
 		  EXTI->PR = GPIO_PIN_5_MSK;
 		  __CALL(X_CallBack_EXTI.L5);}

 	  if(EXTI->PR & GPIO_PIN_6_MSK){
 		  EXTI->PR = GPIO_PIN_6_MSK;
 		  __CALL(X_CallBack_EXTI.L6);}

 	  if(EXTI->PR & GPIO_PIN_7_MSK){
 		  EXTI->PR = GPIO_PIN_7_MSK;
 		  __CALL(X_CallBack_EXTI.L7);}

 	  if(EXTI->PR & GPIO_PIN_8_MSK){
 		  EXTI->PR = GPIO_PIN_8_MSK;
 		  __CALL(X_CallBack_EXTI.L8);}

 	  if(EXTI->PR & GPIO_PIN_9_MSK){
 		  EXTI->PR = GPIO_PIN_9_MSK;
 		  __CALL(X_CallBack_EXTI.L9);}
}

static inline void X_EXTI0_IRQHandler(void){
	EXTI->PR = GPIO_PIN_0_MSK;
	__CALL(X_CallBack_EXTI.L0);
}

static inline void X_EXTI1_IRQHandler(void){
	EXTI->PR = GPIO_PIN_1_MSK;
	__CALL(X_CallBack_EXTI.L1);
}

static inline void X_EXTI2_IRQHandler(void){
	EXTI->PR = GPIO_PIN_2_MSK;
	__CALL(X_CallBack_EXTI.L2);
}

static inline void X_EXTI3_IRQHandler(void){
	EXTI->PR = GPIO_PIN_3_MSK;
	__CALL(X_CallBack_EXTI.L3);
}

static inline void X_EXTI4_IRQHandler(void){
	EXTI->PR = GPIO_PIN_4_MSK;
	__CALL(X_CallBack_EXTI.L4);
}

// X_IRQHandler for TIM1_BRK
static inline void X_TIM1_BRK_IRQHandler(void){
 	TIM1->SR = ~TIM_SR_BIF;
 	__CALL( X_CallBack_TIM1.BRK);
}

// X_IRQHandler for TIM1_UP
static inline void X_TIM1_UP_IRQHandler(void){
 		TIM1->SR = ~TIM_SR_UIF;
 		__CALL( X_CallBack_TIM1.UP);
}

// X_IRQHandler for TIM1_TRG_COM
static inline void X_TIM1_TRG_COM_IRQHandler(void){

 	if( (TIM1->DIER & TIM_DIER_TIE) && (TIM1->SR & TIM_SR_TIF) ){
 		TIM1->SR = ~TIM_SR_TIF;
 		__CALL( X_CallBack_TIM1.TRG );}

 	if( (TIM1->DIER & TIM_DIER_COMIE) && (TIM1->SR & TIM_SR_COMIF) ){
 		TIM1->SR = ~TIM_SR_COMIF;
 		__CALL( X_CallBack_TIM1.COM);}

}

static inline void X_TIM1_CC_IRQHandler(void){

 	if( (TIM1->DIER & TIM_DIER_CC1IE) && (TIM1->SR & TIM_SR_CC1IF)){
 		TIM1->SR = ~TIM_SR_CC1IF;
 		__CALL(X_CallBack_TIM1.CC1);}

 	if( (TIM1->DIER & TIM_DIER_CC2IE) && (TIM1->SR & TIM_SR_CC2IF)){
 		TIM1->SR = ~TIM_SR_CC2IF;
 		__CALL(X_CallBack_TIM1.CC2);}

 	if( (TIM1->DIER & TIM_DIER_CC3IE) && (TIM1->SR & TIM_SR_CC3IF)){
 		TIM1->SR = ~TIM_SR_CC3IF;
 		__CALL(X_CallBack_TIM1.CC3);}

 	if( (TIM1->DIER & TIM_DIER_CC4IE) && (TIM1->SR & TIM_SR_CC4IF)){
 		TIM1->SR = ~TIM_SR_CC4IF;
 		__CALL(X_CallBack_TIM1.CC4);}
}



static inline void X_TIM2_IRQHandler (void){

 	if( (TIM2->DIER & TIM_DIER_UIE) && (TIM2->SR & TIM_SR_UIF) ){
 		TIM2->SR = ~TIM_SR_UIF;
 		__CALL(X_CallBack_TIM2.UP);}

 	if( (TIM2->DIER & TIM_DIER_CC1IE) && (TIM2->SR & TIM_SR_CC1IF) ){
 		TIM2->SR = ~TIM_SR_CC1IF;
 		__CALL(X_CallBack_TIM2.CC1);}

 	if( (TIM2->DIER & TIM_DIER_CC2IE) && (TIM2->SR & TIM_SR_CC2IF) ){
 		TIM2->SR = ~TIM_SR_CC2IF;
 		__CALL(X_CallBack_TIM2.CC2);}

 	if( (TIM2->DIER & TIM_DIER_CC3IE) && (TIM2->SR & TIM_SR_CC3IF) ){
 		TIM2->SR = ~TIM_SR_CC3IF;
 		__CALL(X_CallBack_TIM2.CC3);}

 	if( (TIM2->DIER & TIM_DIER_CC4IE) && (TIM2->SR & TIM_SR_CC4IF) ){
 		TIM2->SR = ~TIM_SR_CC4IF;
 		__CALL(X_CallBack_TIM2.CC4);}

 	if( (TIM2->DIER & TIM_DIER_TIE) && (TIM2->SR & TIM_SR_TIF) ){
 		TIM2->SR = ~TIM_SR_TIF;
 		__CALL(X_CallBack_TIM2.TRG);}
}



static inline void X_TIM3_IRQHandler (void){

 	if( (TIM3->DIER & TIM_DIER_UIE) && (TIM3->SR & TIM_SR_UIF) ){
 		TIM3->SR = ~TIM_SR_UIF;
 		__CALL(X_CallBack_TIM3.UP);}

 	if( (TIM3->DIER & TIM_DIER_CC1IE) && (TIM3->SR & TIM_SR_CC1IF) ){
 		TIM3->SR = ~TIM_SR_CC1IF;
 		__CALL(X_CallBack_TIM3.CC1);}

 	if( (TIM3->DIER & TIM_DIER_CC2IE) && (TIM3->SR & TIM_SR_CC2IF) ){
 		TIM3->SR = ~TIM_SR_CC2IF;
 		__CALL(X_CallBack_TIM3.CC2);}

 	if( (TIM3->DIER & TIM_DIER_CC3IE) && (TIM3->SR & TIM_SR_CC3IF) ){
 		TIM3->SR = ~TIM_SR_CC3IF;
 		__CALL(X_CallBack_TIM3.CC3);}

 	if( (TIM3->DIER & TIM_DIER_CC4IE) && (TIM3->SR & TIM_SR_CC4IF) ){
 		TIM3->SR = ~TIM_SR_CC4IF;
 		__CALL(X_CallBack_TIM3.CC4);}

 	if( (TIM3->DIER & TIM_DIER_TIE) && (TIM3->SR & TIM_SR_TIF) ){
 		TIM3->SR = ~TIM_SR_TIF;
 		__CALL(X_CallBack_TIM3.TRG);}
}


static inline void X_TIM4_IRQHandler (void){

 	if( (TIM4->DIER & TIM_DIER_UIE) && (TIM4->SR & TIM_SR_UIF) ){
 		TIM4->SR = ~TIM_SR_UIF;
 		__CALL(X_CallBack_TIM2.UP);}

 	if( (TIM4->DIER & TIM_DIER_CC1IE) && (TIM4->SR & TIM_SR_CC1IF) ){
 		TIM4->SR = ~TIM_SR_CC1IF;
 		__CALL(X_CallBack_TIM2.CC1);}

 	if( (TIM4->DIER & TIM_DIER_CC2IE) && (TIM4->SR & TIM_SR_CC2IF) ){
 		TIM4->SR = ~TIM_SR_CC2IF;
 		__CALL(X_CallBack_TIM2.CC2);}

 	if( (TIM4->DIER & TIM_DIER_CC3IE) && (TIM4->SR & TIM_SR_CC3IF) ){
 		TIM4->SR = ~TIM_SR_CC3IF;
 		__CALL(X_CallBack_TIM2.CC3);}

 	if( (TIM4->DIER & TIM_DIER_CC4IE) && (TIM4->SR & TIM_SR_CC4IF) ){
 		TIM4->SR = ~TIM_SR_CC4IF;
 		__CALL(X_CallBack_TIM2.CC4);}

 	if( (TIM4->DIER & TIM_DIER_TIE) && (TIM4->SR & TIM_SR_TIF) ){
 		TIM4->SR = ~TIM_SR_TIF;
 		__CALL(X_CallBack_TIM2.TRG);}
}


static inline void X_ADC1_IRQHandler(void){

 	if( (ADC1->SR & ADC_SR_EOC) && (ADC1->CR1 && ADC_CR1_EOCIE) ){
 		ADC1->SR = ~ADC_SR_EOC;
 		__CALL(X_CallBack_ADC1.EOC);}

 	if( (ADC1->SR & ADC_SR_JEOC) && (ADC1->CR1 & ADC_CR1_JEOCIE) ){
 		ADC1->SR = ~ADC_SR_JEOC;
 		__CALL(X_CallBack_ADC1.JEOC);}

 	if( (ADC1->SR & ADC_SR_AWD) && (ADC1->CR1 & ADC_CR1_AWDIE) ){
 		ADC1->SR = ~ADC_SR_AWD;
 		__CALL(X_CallBack_ADC1.AWD);}
}



static inline void X_ADC2_IRQHandler(void){

 	if( (ADC2->SR & ADC_SR_EOC) && (ADC2->CR1 && ADC_CR1_EOCIE) ){
 		ADC2->SR = ~ADC_SR_EOC;
 		__CALL(X_CallBack_ADC2.EOC);}

 	if( (ADC2->SR & ADC_SR_JEOC) && (ADC2->CR1 & ADC_CR1_JEOCIE) ){
 		ADC2->SR = ~ADC_SR_JEOC;
 		__CALL(X_CallBack_ADC2.JEOC);}

 	if( (ADC2->SR & ADC_SR_AWD) && (ADC2->CR1 & ADC_CR1_AWDIE) ){
 		ADC2->SR = ~ADC_SR_AWD;
 		__CALL(X_CallBack_ADC2.AWD);}
}


static inline void X_DMA1_Channel1_IRQHandler(void){

  	if( (DMA1->ISR & DMA_ISR_TCIF1) && (DMA1_Channel1->CCR & DMA_CCR_TCIE) ){
  			DMA1->IFCR = DMA_IFCR_CTCIF1;
  			__CALL( X_CallBack_DMA1_Ch1.TC);}

  	if( (DMA1->ISR & DMA_ISR_HTIF1) && (DMA1_Channel1->CCR & DMA_CCR_HTIE) ){
  			DMA1->IFCR = DMA_IFCR_CHTIF1;
  			__CALL( X_CallBack_DMA1_Ch1.HT);}

  	if( (DMA1->ISR & DMA_ISR_TEIF1) && (DMA1_Channel1->CCR & DMA_CCR_TEIE) ){
  			DMA1->IFCR = DMA_IFCR_CTEIF1;
  			__CALL( X_CallBack_DMA1_Ch1.TE);}
}
 // X_IRQHandler for DMA1_Channel2
static inline void X_DMA1_Channel2_IRQHandler(void){

  	if( (DMA1->ISR & DMA_ISR_TCIF2) && (DMA1_Channel2->CCR & DMA_CCR_TCIE) ){
  			DMA1->IFCR = DMA_IFCR_CTCIF2;
  			__CALL( X_CallBack_DMA1_Ch2.TC);}

  	if( (DMA1->ISR & DMA_ISR_HTIF2) && (DMA1_Channel2->CCR & DMA_CCR_HTIE) ){
  			DMA1->IFCR = DMA_IFCR_CHTIF2;
  			__CALL( X_CallBack_DMA1_Ch2.HT);}

  	if( (DMA1->ISR & DMA_ISR_TEIF2) && (DMA1_Channel2->CCR & DMA_CCR_TEIE) ){
  			DMA1->IFCR = DMA_IFCR_CTEIF2;
  			__CALL( X_CallBack_DMA1_Ch2.TE);}
}
 // X_IRQHandler for DMA1_Channel3
static inline void X_DMA1_Channel3_IRQHandler(void){

	if( (DMA1->ISR & DMA_ISR_TCIF3) && (DMA1_Channel3->CCR & DMA_CCR_TCIE) ){
		DMA1->IFCR = DMA_IFCR_CTCIF3;
  		__CALL( X_CallBack_DMA1_Ch3.TC);}

  	if( (DMA1->ISR & DMA_ISR_HTIF3) && (DMA1_Channel3->CCR & DMA_CCR_HTIE) ){
  			DMA1->IFCR = DMA_IFCR_CHTIF3;
  			__CALL( X_CallBack_DMA1_Ch3.HT);}

  	if( (DMA1->ISR & DMA_ISR_TEIF3) && (DMA1_Channel3->CCR & DMA_CCR_TEIE) ){
  			DMA1->IFCR = DMA_IFCR_CTEIF3;
  			__CALL( X_CallBack_DMA1_Ch3.TE);}
 }


static inline void X_DMA1_Channel4_IRQHandler(void){

 	if( (DMA1->ISR & DMA_ISR_TCIF4) && (DMA1_Channel4->CCR & DMA_CCR_TCIE) ){
 			DMA1->IFCR = DMA_IFCR_CTCIF4;
 			__CALL( X_CallBack_DMA1_Ch4.TC);}

 	if( (DMA1->ISR & DMA_ISR_HTIF4) && (DMA1_Channel4->CCR & DMA_CCR_HTIE) ){
 			DMA1->IFCR = DMA_IFCR_CHTIF4;
 			__CALL( X_CallBack_DMA1_Ch4.HT);}

 	if( (DMA1->ISR & DMA_ISR_TEIF4) && (DMA1_Channel4->CCR & DMA_CCR_TEIE) ){
 			DMA1->IFCR = DMA_IFCR_CTEIF4;
 			__CALL( X_CallBack_DMA1_Ch4.TE);}
}

static inline void X_DMA1_Channel5_IRQHandler(void){

  	if( (DMA1->ISR & DMA_ISR_TCIF5) && (DMA1_Channel5->CCR & DMA_CCR_TCIE) ){
  			DMA1->IFCR = DMA_IFCR_CTCIF5;
  			__CALL( X_CallBack_DMA1_Ch5.TC);}

  	if( (DMA1->ISR & DMA_ISR_HTIF5) && (DMA1_Channel5->CCR & DMA_CCR_HTIE) ){
  			DMA1->IFCR = DMA_IFCR_CHTIF5;
  			__CALL( X_CallBack_DMA1_Ch5.HT);}

  	if( (DMA1->ISR & DMA_ISR_TEIF5) && (DMA1_Channel5->CCR & DMA_CCR_TEIE) ){
  			DMA1->IFCR = DMA_IFCR_CTEIF5;
  			__CALL( X_CallBack_DMA1_Ch5.TE);}
}

static inline void X_DMA1_Channel6_IRQHandler(void){

 	if( (DMA1->ISR & DMA_ISR_TCIF6) && (DMA1_Channel6->CCR & DMA_CCR_TCIE) ){
 			DMA1->IFCR = DMA_IFCR_CTCIF6;
 			__CALL( X_CallBack_DMA1_Ch6.TC);}

 	if( (DMA1->ISR & DMA_ISR_HTIF6) && (DMA1_Channel6->CCR & DMA_CCR_HTIE) ){
 			DMA1->IFCR = DMA_IFCR_CHTIF6;
 			__CALL( X_CallBack_DMA1_Ch6.HT);}

 	if( (DMA1->ISR & DMA_ISR_TEIF6) && (DMA1_Channel6->CCR & DMA_CCR_TEIE) ){
 			DMA1->IFCR = DMA_IFCR_CTEIF6;
 			__CALL( X_CallBack_DMA1_Ch6.TE);}
}

static inline void X_DMA1_Channel7_IRQHandler(void){

 	if( (DMA1->ISR & DMA_ISR_TCIF7) && (DMA1_Channel7->CCR & DMA_CCR_TCIE) ){
 			DMA1->IFCR = DMA_IFCR_CTCIF7;
 			__CALL( X_CallBack_DMA1_Ch7.TC);}

 	if( (DMA1->ISR & DMA_ISR_HTIF7) && (DMA1_Channel7->CCR & DMA_CCR_HTIE) ){
 			DMA1->IFCR = DMA_IFCR_CHTIF7;
 			__CALL( X_CallBack_DMA1_Ch7.HT);}

 	if( (DMA1->ISR & DMA_ISR_TEIF7) && (DMA1_Channel7->CCR & DMA_CCR_TEIE) ){
 			DMA1->IFCR = DMA_IFCR_CTEIF7;
 			__CALL( X_CallBack_DMA1_Ch7.TE);}
}

static inline void X_USART1_IRQHandler(void){

	if( (USART1->SR & USART_SR_TC) && (USART1->CR1 & USART_CR1_TCIE) ){
	 		//Clear flag : Read USART_SR followed a write to USART_DR

	 		//Calling callback function :
	 		__CALL(X_CallBack_USART1.TC);}

	 	if( (USART1->SR & USART_SR_TXE) && (USART1->CR1 & USART_CR1_TXEIE) ){
	 		//Clear flag : write to DR register

	 		//Calling callback function :
	 		__CALL(X_CallBack_USART1.TXE);}

	 	if( (USART1->SR & USART_SR_CTS) && (USART1->CR3 & USART_CR3_CTSIE) ){
	 		//Clear flag :
	 		USART1->SR = ~USART_SR_CTS;
	 		//Calling callback function :
	 		__CALL(X_CallBack_USART1.CTS);}

	 	if( (USART1->SR & USART_SR_IDLE) && (USART1->CR1 & USART_CR1_IDLEIE) ){
	 		//Clear flag : Read USART_SR followed by read USART_DR

	 		//Calling callback function :
	 		__CALL(X_CallBack_USART1.IDLE);}

	 	if( (USART1->SR & USART_SR_RXNE) && (USART1->CR1 & USART_CR1_RXNEIE) ){
	 		//Clear flag : Read USART_DR or write zero

	 		//Calling callback function :
	 		__CALL(X_CallBack_USART1.RXNE);}

	 	if( (USART1->SR & USART_SR_PE) && (USART1->CR1 & USART_CR1_PEIE) ){
	 		//Clear flag : Read USART_SR followed by read USART_DR
	 		//RXNE flag should be set before clearing

	 		//Calling callback function :
	 		__CALL(X_CallBack_USART1.PE);}

	 	if( (USART1->SR & USART_SR_LBD) && (USART1->CR2 & USART_CR2_LBDIE) ){
	 		//Clear flag :
	 		USART1->SR = ~USART_SR_LBD;
	 		//Calling callback function :
	 		__CALL(X_CallBack_USART1.LBD);
	 	}

	 	if( (USART1->SR & USART_SR_ORE) && (USART1->CR1 & USART_CR1_RXNEIE) ){
	 		//Clear flag : Read USART_SR followed by read USART_DR

	 		//Calling callback function :
	 		__CALL(X_CallBack_USART1.ORE);}


}

static inline void X_USART2_IRQHandler(void){

	if( (USART2->SR & USART_SR_TC) && (USART2->CR1 & USART_CR1_TCIE) ){
	 		//Clear flag : Read USART_SR followed a write to USART_DR

	 		//Calling callback function :
	 		__CALL(X_CallBack_USART2.TC);}

	 	if( (USART2->SR & USART_SR_TXE) && (USART2->CR1 & USART_CR1_TXEIE) ){
	 		//Clear flag : write to DR register

	 		//Calling callback function :
	 		__CALL(X_CallBack_USART2.TXE);}

	 	if( (USART2->SR & USART_SR_CTS) && (USART2->CR3 & USART_CR3_CTSIE) ){
	 		//Clear flag :
	 		USART2->SR = ~USART_SR_CTS;
	 		//Calling callback function :
	 		__CALL(X_CallBack_USART2.CTS);}

	 	if( (USART2->SR & USART_SR_IDLE) && (USART2->CR1 & USART_CR1_IDLEIE) ){
	 		//Clear flag : Read USART_SR followed by read USART_DR

	 		//Calling callback function :
	 		__CALL(X_CallBack_USART2.IDLE);}

	 	if( (USART2->SR & USART_SR_RXNE) && (USART2->CR1 & USART_CR1_RXNEIE) ){
	 		//Clear flag : Read USART_DR or write zero

	 		//Calling callback function :
	 		__CALL(X_CallBack_USART2.RXNE);}

	 	if( (USART2->SR & USART_SR_PE) && (USART2->CR1 & USART_CR1_PEIE) ){
	 		//Clear flag : Read USART_SR followed by read USART_DR
	 		//RXNE flag should be set before clearing

	 		//Calling callback function :
	 		__CALL(X_CallBack_USART2.PE);}

	 	if( (USART2->SR & USART_SR_LBD) && (USART2->CR2 & USART_CR2_LBDIE) ){
	 		//Clear flag :
	 		USART2->SR = ~USART_SR_LBD;
	 		//Calling callback function :
	 		__CALL(X_CallBack_USART2.LBD);
	 	}

	 	if( (USART2->SR & USART_SR_ORE) && (USART2->CR1 & USART_CR1_RXNEIE) ){
	 		//Clear flag : Read USART_SR followed by read USART_DR

	 		//Calling callback function :
	 		__CALL(X_CallBack_USART2.ORE);}


}


static inline void X_USART3_IRQHandler(void){

	if( (USART3->SR & USART_SR_TC) && (USART3->CR1 & USART_CR1_TCIE) ){
	 		//Clear flag : Read USART_SR followed a write to USART_DR

	 		//Calling callback function :
	 		__CALL(X_CallBack_USART3.TC);}

	 	if( (USART3->SR & USART_SR_TXE) && (USART3->CR1 & USART_CR1_TXEIE) ){
	 		//Clear flag : write to DR register

	 		//Calling callback function :
	 		__CALL(X_CallBack_USART3.TXE);}

	 	if( (USART3->SR & USART_SR_CTS) && (USART3->CR3 & USART_CR3_CTSIE) ){
	 		//Clear flag :
	 		USART3->SR = ~USART_SR_CTS;
	 		//Calling callback function :
	 		__CALL(X_CallBack_USART3.CTS);}

	 	if( (USART3->SR & USART_SR_IDLE) && (USART3->CR1 & USART_CR1_IDLEIE) ){
	 		//Clear flag : Read USART_SR followed by read USART_DR

	 		//Calling callback function :
	 		__CALL(X_CallBack_USART3.IDLE);}

	 	if( (USART3->SR & USART_SR_RXNE) && (USART3->CR1 & USART_CR1_RXNEIE) ){
	 		//Clear flag : Read USART_DR or write zero

	 		//Calling callback function :
	 		__CALL(X_CallBack_USART3.RXNE);}

	 	if( (USART3->SR & USART_SR_PE) && (USART3->CR1 & USART_CR1_PEIE) ){
	 		//Clear flag : Read USART_SR followed by read USART_DR
	 		//RXNE flag should be set before clearing

	 		//Calling callback function :
	 		__CALL(X_CallBack_USART3.PE);}

	 	if( (USART3->SR & USART_SR_LBD) && (USART3->CR2 & USART_CR2_LBDIE) ){
	 		//Clear flag :
	 		USART3->SR = ~USART_SR_LBD;
	 		//Calling callback function :
	 		__CALL(X_CallBack_USART3.LBD);
	 	}

	 	if( (USART3->SR & USART_SR_ORE) && (USART3->CR1 & USART_CR1_RXNEIE) ){
	 		//Clear flag : Read USART_SR followed by read USART_DR

	 		//Calling callback function :
	 		__CALL(X_CallBack_USART3.ORE);}


}

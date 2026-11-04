#include <X_general.h>


uint32_t SystemCoreClock=72000000 ;
volatile uint32_t  uwTick;

void delay(unsigned int time){

	for(int i=0;i<time;i++)
		for(int j=0;j<time;j++);


}

void X_System_Init(void){

	// Set Interrupt Group Priority
	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4__4_pre_0_sub);

	// Config systick
	SysTick_Config( SystemCoreClock/1000);

	// systick interrupt
	uint32_t prioritygroup = NVIC_GetPriorityGrouping();
	NVIC_SetPriority(SysTick_IRQn , NVIC_EncodePriority(prioritygroup, 11, 0));

	// in
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

	AFIO->MAPR &= ~AFIO_MAPR_SWJ_CFG;
	AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_1;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

}



void X_Delay_ms(uint32_t Delay){

	uint32_t tickstart = uwTick;
	uint32_t wait = Delay;

	while ((uwTick - tickstart) < wait);
}


void X_Clock_Init_72MHz(void){
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

  /* Reset the RCC clock configuration to the default reset state(for debug purpose) */
  /* Set HSION bit */
  RCC->CR |= (uint32_t)0x00000001;

  /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
  RCC->CFGR &= (uint32_t)0xF8FF0000;


  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFF;

  /* Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
  RCC->CFGR &= (uint32_t)0xFF80FFFF;

  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x009F0000;


  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
   /* Enable HSE */
   RCC->CR |= ((uint32_t)RCC_CR_HSEON);

   /* Wait till HSE is ready and if Time out is reached exit */
   do
   {
     HSEStatus = RCC->CR & RCC_CR_HSERDY;
     StartUpCounter++;
   } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

   if ((RCC->CR & RCC_CR_HSERDY) != 0)
   {
     HSEStatus = (uint32_t)0x01;
   }
   else
   {
     HSEStatus = (uint32_t)0x00;
   }

   if (HSEStatus == (uint32_t)0x01)
   {
     /* Enable Prefetch Buffer */
     FLASH->ACR |= FLASH_ACR_PRFTBE;

     /* Flash 2 wait state */
     FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
     FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;


     /* HCLK = SYSCLK */
     RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;

     /* PCLK2 = HCLK */
     RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;

     /* PCLK1 = HCLK */
     RCC->CFGR |= ((uint32_t)RCC_CFGR_PPRE1_DIV2|RCC_CFGR_ADCPRE);


     /*  PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
     RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE |
                                         RCC_CFGR_PLLMULL));
     RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL9);

     /* Enable PLL */
     RCC->CR |= RCC_CR_PLLON;

     /* Wait till PLL is ready */
     while((RCC->CR & RCC_CR_PLLRDY) == 0)
     {
     }

     /* Select PLL as system clock source */
     RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
     RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

     /* Wait till PLL is used as system clock source */
     while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
     {
     }
   }
   else
   { /* If HSE fails to start-up, the application will have wrong clock
          configuration. User can add here some code to deal with this error */
   }




}

void X_Clock_Init_8MHz (void){
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

  /* Reset the RCC clock configuration to the default reset state(for debug purpose) */
  /* Set HSION bit */
  RCC->CR |= (uint32_t)0x00000001;

  /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
  RCC->CFGR &= (uint32_t)0xF8FF0000;


  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFF;

  /* Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
  RCC->CFGR &= (uint32_t)0xFF80FFFF;

  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x009F0000;


  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
   /* Enable HSE */
   RCC->CR |= ((uint32_t)RCC_CR_HSEON);

   /* Wait till HSE is ready and if Time out is reached exit */
   do
   {
     HSEStatus = RCC->CR & RCC_CR_HSERDY;
     StartUpCounter++;
   } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

   if ((RCC->CR & RCC_CR_HSERDY) != 0)
   {
     HSEStatus = (uint32_t)0x01;
   }
   else
   {
     HSEStatus = (uint32_t)0x00;
   }

   if (HSEStatus == (uint32_t)0x01)
   {
     /* Enable Prefetch Buffer */
     FLASH->ACR |= FLASH_ACR_PRFTBE;

     /* Flash 2 wait state */
     FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
     FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;


     /* HCLK = SYSCLK */
     RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV2;

     /* PCLK2 = HCLK */
     RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;

     /* PCLK1 = HCLK */
     RCC->CFGR |= ((uint32_t)RCC_CFGR_PPRE1_DIV2);


     /*  PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
     RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE |
                                         RCC_CFGR_PLLMULL));
     RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC );

     /* Enable PLL */
     RCC->CR |= RCC_CR_PLLON;

     /* Wait till PLL is ready */
     while((RCC->CR & RCC_CR_PLLRDY) == 0)
     {
     }

     /* Select PLL as system clock source */
     RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
     RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

     /* Wait till PLL is used as system clock source */
     while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
     {
     }
   }
   else
   { /* If HSE fails to start-up, the application will have wrong clock
          configuration. User can add here some code to deal with this error */
   }




}



void X_RCC_MCO(void){

	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

	GPIOA->CRH |= GPIO_CRH_MODE8;

	GPIOA->CRH &= ~GPIO_CRH_CNF8;
	GPIOA->CRH |= GPIO_CRH_CNF8_1;

	RCC->CFGR = RCC_CFGR_MCO;

}


int _write(int file, char *ptr,int len){
	int DataIdx;
	for(DataIdx=0 ;DataIdx<len ;DataIdx++)
		ITM_SendChar(*ptr++);
	return len;
}



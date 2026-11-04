#include "usart.h"

X_UART_StateTypeDef USART3_Status = X_UART_STATE_READY;


X_StatusTypeDef usart_trasmit_timeout(uint8_t * Data,uint32_t size,uint32_t timeout){

	if(USART3_Status != X_UART_STATE_READY){
		return X_BUSY;}

	USART3_Status = X_UART_STATE_BUSY_TX;

	uint32_t TxCount = size;
	uint8_t * pData=Data;
	uint32_t tickstart=uwTick;

	while(TxCount>0){

		while(!(USART3->SR & USART_SR_TXE)){
			if((uwTick - tickstart)>timeout){
				USART3_Status = X_UART_STATE_READY;
				return X_TIMEOUT;}
		}

		USART3->DR = *pData;
		pData++;
		TxCount--;
	}

	while(!(USART3->SR & USART_SR_TC)){
		if((uwTick - tickstart)>timeout){
			USART3_Status = X_UART_STATE_READY;
			return X_TIMEOUT;}
	}


	USART3_Status = X_UART_STATE_READY;
	return X_OK;


}


X_StatusTypeDef usart_rx_timeout(uint8_t * Data,uint32_t size,uint32_t timeout){

	if(USART3_Status != X_UART_STATE_READY){
		return X_BUSY;}

	USART3_Status = X_UART_STATE_BUSY_RX;

	uint32_t RxCount = size;
	uint8_t * pData=Data;
	uint32_t tickstart=uwTick;

	while(RxCount>0){

		while(!(USART3->SR & USART_SR_RXNE)){
			if((uwTick - tickstart)>timeout){
				USART3_Status = X_UART_STATE_READY;
				return X_TIMEOUT;}
		}

		*pData = USART3->DR;
		pData++;
		RxCount--;
	}

	USART3_Status = X_UART_STATE_READY;
	return X_OK;
}

void usart_trasmit(uint8_t * Data,uint32_t size){

	uint32_t TxCount = size;
	uint8_t * pData=Data;

	while(TxCount>0){

		USART3->DR = *pData;
		pData++;
		TxCount--;

		while(!(USART3->SR & USART_SR_TXE)){}
}


}



void usart_tc_callback(void){

	USART3->SR = ~USART_SR_TC;
	USART3_Status = X_UART_STATE_READY;
	USART3->CR1 &= ~USART_CR1_TCIE;

}

void usart_init(void){

	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;

	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

	GPIOB->CRH &= ~(GPIO_CRH_MODE10|GPIO_CRH_CNF10);
	GPIOB->CRH |= (GPIO_CRH_MODE10_1|GPIO_CRH_CNF10_1);

	GPIOB->CRH &= ~(GPIO_CRH_MODE11|GPIO_CRH_CNF11);
	GPIOB->CRH |= GPIO_CRH_CNF11_0;

	USART3->CR1 |= USART_CR1_UE;

	USART3->CR1 &= ~USART_CR1_M;
	USART3->CR2 &= ~USART_CR2_STOP;

	//baudrate = 115200
	//USART3->BRR = ((19<<4)|8);

	//baudrate =9600
	USART3->BRR = ((234<<4)|6);





	USART3->CR1 |= (USART_CR1_TE);
	USART3->CR1 |= (USART_CR1_RE);



}


void DMA_CH2_usart_tx_callback(void){

	USART3->CR1 |= USART_CR1_TCIE;



}


void usart_tx_dma_init(void){


	X_CallBack_USART3.TC = usart_tc_callback;

	uint32_t PG=NVIC_GetPriorityGrouping();
	NVIC_SetPriority(USART3_IRQn,NVIC_EncodePriority(PG, 6, 0));
	NVIC_EnableIRQ(USART3_IRQn);


	USART3->CR3 |= USART_CR3_DMAT;

	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	DMA1_Channel2->CPAR = (uint32_t)(&USART3->DR);
	DMA1_Channel2->CCR = 0x0;
	DMA1_Channel2->CCR |= ( DMA_CCR_MINC | DMA_CCR_DIR | DMA_CCR_TCIE);

	X_CallBack_DMA1_Ch2.TC = DMA_CH2_usart_tx_callback;

	NVIC_GetPriorityGrouping();
	NVIC_SetPriority(DMA1_Channel2_IRQn,NVIC_EncodePriority(PG, 5, 0));
	NVIC_EnableIRQ(DMA1_Channel2_IRQn);

}



X_StatusTypeDef usart_tx_dma_start(uint8_t * data,uint32_t size){


	if(USART3_Status != X_UART_STATE_READY){
		return X_BUSY;}

	USART3_Status = X_UART_STATE_BUSY_TX;

	DMA1_Channel2->CCR &= ~DMA_CCR_EN;
	DMA1_Channel2->CNDTR = size;
	DMA1_Channel2->CMAR = (uint32_t)data;
	DMA1_Channel2->CCR |= DMA_CCR_EN;

	return X_OK;

}











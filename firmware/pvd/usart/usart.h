#pragma once

#include <X_general.h>

typedef enum
{
  X_UART_STATE_RESET             = 0x00U,    /*!< Peripheral is not yet Initialized
                                                Value is allowed for gState and RxState */
  X_UART_STATE_READY             = 0x20U,    /*!< Peripheral Initialized and ready for use
                                                Value is allowed for gState and RxState */
  X_UART_STATE_BUSY              = 0x24U,    /*!< an internal process is ongoing
                                                Value is allowed for gState only */
  X_UART_STATE_BUSY_TX           = 0x21U,    /*!< Data Transmission process is ongoing
                                                Value is allowed for gState only */
  X_UART_STATE_BUSY_RX           = 0x22U,    /*!< Data Reception process is ongoing
                                                Value is allowed for RxState only */
  X_UART_STATE_BUSY_TX_RX        = 0x23U,    /*!< Data Transmission and Reception process is ongoing
                                                Not to be used for neither gState nor RxState.
                                                Value is result of combination (Or) between gState and RxState values */
  X_UART_STATE_TIMEOUT           = 0xA0U,    /*!< Timeout state
                                                Value is allowed for gState only */
  X_UART_STATE_ERROR             = 0xE0U     /*!< Error
                                                Value is allowed for gState only */
} X_UART_StateTypeDef;

void usart_trasmit(uint8_t * Data,uint32_t size);
void usart_init(void);
void usart_tx_dma_init(void);
X_StatusTypeDef usart_tx_dma_start(uint8_t * data,uint32_t size);
X_StatusTypeDef usart_trasmit_timeout(uint8_t * Data,uint32_t size,uint32_t timeout);
X_StatusTypeDef usart_rx_timeout(uint8_t * Data,uint32_t size,uint32_t timeout);


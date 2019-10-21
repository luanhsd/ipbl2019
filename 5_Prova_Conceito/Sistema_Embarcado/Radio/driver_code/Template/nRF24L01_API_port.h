/*
 ******************************************************************************
 * @file    nRF24L01_API_port.c
 * @author  V�tor Eduardo Sabadine da Cruz
 * @version 0
 * @date    10-Outubro-2019
 * @brief   M�quina de estados para tratamento de sensor gen�rico.
 ******************************************************************************
 */

#include "fsl_spi_master_driver.h"
#include "fsl_gpio_driver.h"
#include "gpio1.h"
#include "task.h"
#include "fsl_os_abstraction_free_rtos.h"

extern task_handler_t TaskRadio1_task_handler;
extern task_handler_t TaskRadio2_task_handler;

semaphore_t nRF24L01_Radio1_IRQ = NULL;
semaphore_t nRF24L01_Radio2_IRQ = NULL;

const spi_master_user_config_t Radio_MasterConfig0 = {
	.bitsPerSec = 2000000U,
	.polarity = kSpiClockPolarity_ActiveHigh,
	.phase = kSpiClockPhase_FirstEdge,
	.direction = kSpiMsbFirst
};

spi_master_state_t Radio_MasterState;
uint32_t Radio_calculatedBaudRate = 0;

bool nRF24L01_SPI_Init_port() {
	bool retVal = true;
	uint32_t instance;

	if (xTaskGetCurrentTaskHandle() == TaskRadio1_task_handler) {
		instance = 0;
	} else if (xTaskGetCurrentTaskHandle() == TaskRadio2_task_handler) {
		instance = 1;
	} else {
		return false;
	}
	retVal &=
			(SPI_DRV_MasterInit(instance, &Radio_MasterState) == kStatus_SPI_Success) ? 1 : 0;
	SPI_DRV_MasterConfigureBus(instance, &Radio_MasterConfig0,
			&Radio_calculatedBaudRate);

	return retVal;
}

const gpio_input_pin_user_config_t gpio1_InpConfig0[] = {
  {
    .pinName = J1_6,
    .config.isPullEnable = true,
    .config.isPassiveFilterEnabled = true,
    .config.interrupt = kPortIntFallingEdge
  },
  {
    .pinName = J1_12,
    .config.isPullEnable = true,
    .config.isPassiveFilterEnabled = true,
    .config.interrupt = kPortIntFallingEdge
  },
  {
    .pinName = GPIO_PINS_OUT_OF_RANGE,
  }
};

bool nRF24L01_EXTI_Init_port() {
	/*! gpio1 Auto initialization start */
	GPIO_DRV_WritePinOutput( J1_6, 0 );
	GPIO_DRV_WritePinOutput( J1_12, 0 );

	GPIO_DRV_Init(gpio1_InpConfig0,gpio1_OutConfig0);
	/*! gpio1 Auto initialization end */

	nRF24L01_Radio1_IRQ = xSemaphoreCreateBinary();
	nRF24L01_Radio2_IRQ = xSemaphoreCreateBinary();

	return true;
}


/*
 #define nRF24L01_SPI_TransferBlocking(TX_BUFFER,RX_BUFFER,LENGTH) 		SPI_DRV_MasterTransferBlocking(SPI_ID, &Radio_MasterConfig0, TX_BUFFER, RX_BUFFER, LENGTH, 20);

 #define nRF24L01_writeChpSelectPin( STATE )														GPIO_DRV_WritePinOutput(J2_6, STATE);
 #define nRF24L01_writeCEPin( STATE )																	GPIO_DRV_WritePinOutput(J1_8, STATE);

 */

void nRF24L01_SPI_TransferBlocking(uint8_t* TX_BUFFER, uint8_t* RX_BUFFER,
		uint8_t LENGTH) {
	if (xTaskGetCurrentTaskHandle() == TaskRadio1_task_handler) {
		SPI_DRV_MasterTransferBlocking(0, &Radio_MasterConfig0, TX_BUFFER,
				RX_BUFFER, LENGTH, 20);
	} else {
		SPI_DRV_MasterTransferBlocking(1, &Radio_MasterConfig0, TX_BUFFER,
				RX_BUFFER, LENGTH, 20);
	}
}

void nRF24L01_writeChpSelectPin(uint8_t STATE) {
	if (xTaskGetCurrentTaskHandle() == TaskRadio1_task_handler) {
		GPIO_DRV_WritePinOutput(J2_6, STATE);
	} else {
		GPIO_DRV_WritePinOutput(J2_2, STATE);
	}
}
void nRF24L01_writeCEPin(uint8_t STATE) {
	if (xTaskGetCurrentTaskHandle() == TaskRadio1_task_handler) {
		GPIO_DRV_WritePinOutput(J1_8, STATE);
	} else {
		GPIO_DRV_WritePinOutput(J1_10, STATE);
	}
}

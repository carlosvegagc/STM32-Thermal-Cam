/*
 *  Created on: 25/05/2021
 *      Author: Carlos Vega García
 * Description: This file implements the task for reading the CPU temperature
 * 				and sending it by the cpu_temp_queque.
 *
 */

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"
#include "cmsis_os2.h"

extern ADC_HandleTypeDef hadc1;
extern osMessageQueueId_t cpu_temp_quequeHandle;
extern osMutexId_t usart1MUTEXHandle;

/**
 * @brief Function for obtaining the CPU temp.
 * @param argument: Not used
 * @retval None
 */
void cpuTemperatureTask(void *argument) {
	uint16_t rawValue = 0;
	uint32_t ticks = 0;
	float temperature = 0.0;

	HAL_StatusTypeDef hal_status;


	ticks = osKernelGetTickCount();

	for (;;) {

		HAL_ADC_Start(&hadc1);

		hal_status = HAL_ADC_PollForConversion(&hadc1, 10);

		if (hal_status == HAL_OK) {
			rawValue = HAL_ADC_GetValue(&hadc1);
			temperature = ((float)rawValue) / 4095 * 3300;
			temperature = ((temperature-760.0) / 2.5);

			osMessageQueuePut(cpu_temp_quequeHandle, (void*) &temperature, 0, 0);
		}else{

			//Acquire the semaphore for access the USART
			if (osMutexAcquire(usart1MUTEXHandle, 20) == osOK) {

				printf("ERROR Reading the CPU Temp\n");

			}
			//Release the mutex
			osMutexRelease(usart1MUTEXHandle);
		}

		ticks += 500;

		osDelayUntil(ticks);
	}
}

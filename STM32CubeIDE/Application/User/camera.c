/*
 *  Created on: 03/05/2021
 *      Author: Carlos Vega García
 * Description: In this file we implement the functions and tasks
 * 				related with the AMG8833 thermal camera operation.
 *
 */

#include "camera.h"
#include "stm32f4xx_hal_i2c.h"
#include "cmsis_os2.h"
#include <stdio.h>

#define I2C3_TIMEOUT_MAX 0x3000 /*<! The value of the maximal timeout for I2C waiting loops */
#define AMG8833_ADDR  0x69 << 1     /**< @brief Dirección I2C del periferico */
#define THERMISTOR_REG 0x0e         /**< @brief Dirección del Registro del valor del Termistor */
#define PIXEL_1ST_REG 0x80


extern osSemaphoreId_t frameSemHandle;
extern osMutexId_t cameraI2CMutexHandle;
extern osEventFlagsId_t updateBitmapHandle;
extern I2C_HandleTypeDef hi2c3;
extern osMessageQueueId_t temp_queueHandle;
extern osMessageQueueId_t frameRate_queueHandle;

//Functions prototypes
HAL_StatusTypeDef read_temp_register();
HAL_StatusTypeDef read_frame_register(uint16_t *buffer_frame_raw);

/**
 * @brief Function implementing the temperature thread.
 * @param argument: Not used
 * @retval None
 */
void temperature_task(void *argument) {

	uint16_t temperature_raw = 0;
	uint32_t ticks = 0;
	float temperature = 0.0;

	HAL_StatusTypeDef hal_status;

	ticks = osKernelGetTickCount();

	for (;;) {
		hal_status = read_temp_register(&temperature_raw);
		if (hal_status == HAL_OK) {
			temperature = temperature_raw * 0.0625;

			osMessageQueuePut(temp_queueHandle, (void*) &temperature, 0, 0);
		}
		ticks += 500;
		osDelayUntil(ticks);
	}
}

/**
 * @brief Function implementing the frame thread.
 * @param argument: Not used
 * @retval None
 */

void frame_task(void *argument) {

	uint16_t raw_frame_buffer[PIXELS_NUMBER];
	uint32_t ticks = 0;
	uint16_t frame_task_delay = 100;
	uint8_t frame_rate = 10;

	HAL_StatusTypeDef hal_status;

	ticks = osKernelGetTickCount();

	for (;;) {

		osStatus_t os_status;

		hal_status = read_frame_register(raw_frame_buffer);

		if (hal_status == HAL_OK) {
			//Acquire the semaphore for access the global frame buffer
			osSemaphoreAcquire(frameSemHandle, 100);

			//Coping the local buffer to the global buffer with the constant correction.
			for (int i = 0; i < PIXELS_NUMBER; i++) {
				g_raw_frame_buffer[i] = raw_frame_buffer[i];
				g_frame_buffer[i] = raw_frame_buffer[i] * 0.25;
			}

			//Release the semaphore
			osSemaphoreRelease(frameSemHandle);

			// Set the event for updating the bitmap
			osEventFlagsSet (updateBitmapHandle, 0x00000001U);
		} else {
			//printf("ERROR: error leyendo el frame %d\n", hal_status);
		}


		//Check if we need to update the frame rate
		os_status = osMessageQueueGet (frameRate_queueHandle, &frame_rate, 0, 0);
		if (os_status == osOK)
		{
			//Calculates the delay from the frame rate
			frame_task_delay = (1000/frame_rate);
		}


		ticks += frame_task_delay;
		osDelayUntil(ticks);
	}
}




/**
 * @brief Lectura de un FRAME del AMG8833
 *
 * @param buffer_frame_raw: Buffer en el que almacenar el frame leido.
 * @return Hal Status
 */

HAL_StatusTypeDef read_frame_register(uint16_t *buffer_frame_raw) {

	HAL_StatusTypeDef hal_return;
	osStatus_t os_status;

	//Acquire the semaphore for access the global frame buffer
	os_status = osMutexAcquire(cameraI2CMutexHandle, 1000);

	if (os_status == osOK)
	{

		uint8_t buffer[2*PIXELS_NUMBER];

		hal_return = HAL_I2C_Mem_Read(&hi2c3,
				(uint16_t) AMG8833_ADDR,
				(uint16_t) PIXEL_1ST_REG,
				I2C_MEMADD_SIZE_8BIT,
				buffer,
				2*PIXELS_NUMBER,
				50);

		if (hal_return == HAL_OK) {
			for (int i = 0; i < PIXELS_NUMBER; i++) {

				buffer_frame_raw[i] = (((buffer[i*2+1] & 0x07) << 8) | buffer[i*2]);
			}
		}

	}else {
		hal_return = HAL_ERROR;
	}

	//Release the mutex
	osMutexRelease(cameraI2CMutexHandle);

	return hal_return;

}

/**
 * @brief Lectura de un Registro del AMG8833
 *
 * @param temperature_raw: Datos del registro del Termistor del AMG8833
 * @return Hal Status
 */
HAL_StatusTypeDef read_temp_register(uint16_t *temperature_raw) {

	HAL_StatusTypeDef hal_return ;
	uint8_t buffer[2] = { 0, 0 };
	osStatus_t os_status;

	//Acquire the semaphore for access the global frame buffer
	os_status = osMutexAcquire(cameraI2CMutexHandle, 1000);

	if (os_status == osOK)
	{

		hal_return = HAL_I2C_Mem_Read(&hi2c3, (uint16_t) AMG8833_ADDR,
				(uint16_t) THERMISTOR_REG,
				I2C_MEMADD_SIZE_8BIT, buffer, 2, 100);

		if (hal_return == HAL_OK) {
			*temperature_raw = (((buffer[1] & 0x07) << 8) | buffer[0]);

		}



	}else {
		hal_return = HAL_ERROR;
	}

	//Release the semaphore
	osMutexRelease(cameraI2CMutexHandle);
	return hal_return;
}

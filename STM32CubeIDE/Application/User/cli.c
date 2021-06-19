/*
 *  Created on: 03/05/2021
 *      Author: Carlos Vega García
 * Description: In this file we implement the functions and tasks
 * 				related with the USART operation.
 *
 */


#include "stm32f4xx_hal.h"
#include <cmsis_os2.h>
#include "cli.h"
#include "command.h"
#include <string.h> // Para las comparaciones de los comandos
#include <stdlib.h> // Para el atoi
#include <stdio.h>  // Para el printf

#define MEMPOOL_OBJECTS 16
#define MAX_SIZE_PARAM 5

extern UART_HandleTypeDef huart1;
extern osMessageQueueId_t char_queueHandle;
extern osMessageQueueId_t app_msg_queueHandle;
extern osMutexId_t usart1MUTEXHandle;

uint8_t input_buffer[20];
uint8_t index_buffer = 0;
uint8_t input_char;

osMemoryPoolId_t command_MemPool;

/**
 * @brief Inicio de la funcionalidad de Command Line Interface.
 *
 */
void cli_init() {

	printf("Ejercicio de Practica 4 SETR 20-21\r\n");

	//Creates the memory pool
	command_MemPool = osMemoryPoolNew(MEMPOOL_OBJECTS, sizeof(App_Message),
			NULL);

	if (command_MemPool == NULL) {
		//Acquire the semaphore for access the USART
		if (osMutexAcquire(usart1MUTEXHandle, 20) == osOK) {

			printf("ERROR MEMORY POOL\n");

		}
		//Release the mutex
		osMutexRelease(usart1MUTEXHandle);
	}

	HAL_UART_Receive_IT(&huart1, (uint8_t*) &input_char, sizeof(uint8_t));

}

/**
 * @brief UART Receive Complete Callback
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	// Saves received char in the buffer.
	input_buffer[index_buffer] = input_char;

	// Introduce new char in the queue.
	osMessageQueuePut(char_queueHandle, &input_buffer[index_buffer], 0U, 0U);

	// Activates the listening for new characters.
	HAL_UART_Receive_IT(&huart1, (uint8_t*) &input_char, sizeof(uint8_t));

	// Increase the buffer.
	if (index_buffer < 19) {
		index_buffer++;
	} else {
		index_buffer = 0;
	}

}

/**
 * @brief Compara la cadena de texto recibida con la lista de comandos existentes
 *        Si la encuentra complenta el mensaje de aplicación, de lo contrario envia un codigo de mensaje desconocido
 *
 * @param temporal_command
 * @param command_size
 * @param size_command
 * @return
 */
int process_cli_command(uint8_t temporal_command[], uint8_t command_size,
		App_Message *app_command) {

	int command_index = 0;
	app_command->message_code = -1;

	// Checks if any of the commands on cli_command_list corresponds with the
	// incoming command
	while (cli_command_list[command_index].key[0] != 0) {

		int strLength = strlen(cli_command_list[command_index].key);

		if (memcmp(cli_command_list[command_index].key, temporal_command,
				strLength) == 0) {

			//Copy the command code into the app_command.
			app_command->message_code =
					cli_command_list[command_index].command_code;

			//If the found command has additional parameters, copy into the app_command
			if (cli_command_list[command_index].has_parameter > 0) {

				uint8_t posData = 0;

				for (uint8_t pos = (uint8_t) strLength + 1;
						pos < (command_size - 1); pos++) {
					app_command->data[posData] = temporal_command[pos];
					posData++;
				}

				app_command->data[posData + 1] = '\0';
			}

		}
		command_index++;
	}


	//Devolvemos función ayuda
	if (memcmp("help", temporal_command, 4) == 0) {
		//Acquire the semaphore for access the USART
		if (osMutexAcquire(usart1MUTEXHandle, 20) == osOK) {
			printf("**************************************\n");
			printf("**        Comandos Aceptados        **\n");
			printf("**************************************\n");
			printf("help: Lista Comandos disponibles\n");
			command_index = 0;

			while (cli_command_list[command_index].key[0] != 0) {
				printf("%s: %s\n", cli_command_list[command_index].key,
						cli_command_list[command_index].description);
				command_index++;
			}
			printf("**************************************\n");
		}

		//Release the mutex
		osMutexRelease(usart1MUTEXHandle);
	} else {
		if (app_command->message_code < 0) {
			//Acquire the semaphore for access the USART
			if (osMutexAcquire(usart1MUTEXHandle, 0) == osOK) {
				printf("Comando Erróneo\n");

			}
			//Release the mutex
			osMutexRelease(usart1MUTEXHandle);
			return -1;
		}
	}

	return 0;
}

/**
 * @brief Esta tarea recibe caracteres por una cola y va formando un comando. Cuando se recibe el caracter que indica una nueva línea
 * se procesa la cadena recibida para crear un mensaje interno de la aplicación y se envia por la cola al Modelo para que procese el
 * mensaje correspondiente.
 *
 * @param argument
 */
void cli_processing_task(void *argument) {
	uint8_t new_char = 0;
	uint8_t command_size = 0;
	uint8_t temporal_command[20];

	App_Message *app_message = NULL;

	for (;;) {
		osStatus_t os_status;

		// Waits until we receive a new character by the queue.
		os_status = osMessageQueueGet(char_queueHandle, &new_char, NULL, osWaitForever);
		if (os_status == osOK) {

			temporal_command[command_size] = new_char;

			//Acquire the semaphore for access the USART
			if (osMutexAcquire(usart1MUTEXHandle, 0) == osOK) {
				// Sends the feedback
				HAL_UART_Transmit(&huart1, (uint8_t*) &temporal_command[command_size], sizeof(uint8_t), 10);

			}

			//Release the mutex
			osMutexRelease(usart1MUTEXHandle);

			command_size++;

			if (new_char == '\r' && command_size > 1) {


				//Acquire the semaphore for access the USART
				if (osMutexAcquire(usart1MUTEXHandle, 0) == osOK) {
					//Send \n for starting the next command properly
					printf("\n");
				}
				//Release the mutex
				osMutexRelease(usart1MUTEXHandle);


				//Reservar espacio en el Pool con osMemoryPoolAlloc
				app_message = osMemoryPoolAlloc(command_MemPool, 0U);

				//Procesar la cadena recibida en una función a la que le pasamos la
				//cadena y el puntero al espacio de Memoria reservado en el Pool
				int res = process_cli_command(temporal_command, command_size,
						app_message);

				if (res >= 0) {
					// Enviar el mensaje generado por la funcion anterior a la cola de mensajes para el Modelo.
					osMessageQueuePut(app_msg_queueHandle, &app_message, 0U,
							0U);
				} else {
					if (osMemoryPoolFree(command_MemPool, (void*) app_message)
							!= osOK) {
						//Acquire the semaphore for access the USART
						if (osMutexAcquire(usart1MUTEXHandle, 20) == osOK) {

							printf("Error liberando memory pool \n\r");

						}
						//Release the mutex
						osMutexRelease(usart1MUTEXHandle);

					}
				}

				command_size = 0;

			}

			//Check si desborda el buffer
			if (command_size >= (19)) {

				//Acquire the semaphore for access the USART
				if (osMutexAcquire(usart1MUTEXHandle, 20) == osOK) {

					printf("Error cli_processing_task buffer desbordado");

				}
				//Release the mutex
				osMutexRelease(usart1MUTEXHandle);

				command_size = 0;
			}
		} else {

			//Acquire the semaphore for access the USART
			if (osMutexAcquire(usart1MUTEXHandle, 20) == osOK) {

				printf("Error reading the queue on cli processing task");

			}
			//Release the mutex
			osMutexRelease(usart1MUTEXHandle);

		}
	}
}


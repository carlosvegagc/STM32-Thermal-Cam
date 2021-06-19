/*
 * parser.c
 *
 *  Created on: 25 abr. 2021
 *      Author: edavidfs
 */

#include "stm32f4xx_hal.h"
#include <cmsis_os2.h>

#include "cli.h"
#include "command.h"

#include <string.h> // Para las comparaciones de los comandos
#include <stdlib.h> // Para el atoi
#include <stdio.h>  // Para el printf

#define MEMPOOL_OBJECTS 16

extern UART_HandleTypeDef huart1;

extern osMessageQueueId_t char_queueHandle;
extern osMessageQueueId_t app_msg_queueHandle;

uint8_t input_buffer[20];
uint8_t index_buffer = 0;
uint8_t input_char;

osMemoryPoolId_t command_MemPool; /**< Pool de memoria para los comandos **/

/**
 * @brief Inicio de la funcionalidad de Command Line Interface.
 *
 */
void cli_init(){

  printf("Ejercicio de Practica 4 SETR 20-21\r\n");

  // TODO 1: Crear el Pool de memoria y almacenar el identificador en la variable global command_MemPool

  command_MemPool = osMemoryPoolNew(MEMPOOL_OBJECTS, sizeof(App_Message), NULL);

  if(command_MemPool == NULL){
	  printf("ERROR MEMORY POOL\n");
  }


  // TODO 2: Inicia la lectura caracteres de la UART por interrupción
  HAL_UART_Receive_IT(&huart1,(uint8_t*) &input_char,sizeof(uint8_t));


}


/**
 * @brief UART Receive Complete Callback
 */
// TODO 3: Crear la Rutina de servicio de la interrucpión de la UART al recibir un caracter.
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
  // TODO 4: Almacenar el valor recibido
  input_buffer[index_buffer] = input_char;

  // TODO 5: Introducirlo a la Cola de caracteres
  osMessageQueuePut(char_queueHandle, &input_buffer[index_buffer], 0U, 0U);

  // TODO 6: Enviar el Caracter por la UART para que el usuario tenga feedback de lo que está escribiendo
  HAL_UART_Transmit(&huart1,(uint8_t*) &input_buffer[index_buffer],sizeof(uint8_t),100);

  // TODO 7: Solicitar un nuevo caracter a la UART
  HAL_UART_Receive_IT(&huart1, (uint8_t*) &input_char,sizeof(uint8_t));

  // Incrementamos el valor de index buffer
  if(index_buffer < 19){
      index_buffer++;
  }else{
      index_buffer = 0;
  }

}


/**
 * @brief Compara la cadena de texto recibida con la lista de comandos existentes
 *        Si la encuentra complenta el mensaje de aplicación, de lo contrario envia un codigo de mensaje desconocido
 *
 * @param temporal_command
 * @param size_command
 * @return
 */
int process_cli_command(uint8_t temporal_command[], App_Message *app_command) {

  int command_index = 0;

  // TODO 13: Recorrer el array de comandos cli_command_list comparando el parámetro key con la cadena recibida,
  while (cli_command_list[command_index].key[0] != 0) {

    int strLength =  strlen(cli_command_list[command_index].key);
    //printf("%d",strlen(cli_command_list[command_index].key));
    if(memcmp(cli_command_list[command_index].key,temporal_command,strLength)==0){
  // TODO 14: En caso de encontrar el comando completar el mensaje con el código/identidicador correspondiente
  //          Si no se encuentra el comando se devuelve el mensaje de Comando desconocido.
	app_command->message_code = cli_command_list[command_index].command_code;

    }
    command_index++;
  }
  // TODO 15: Opcionalmente se puede devolver el código de comando o de mensaje encontrado si se desea realizar
  //          alguna operación extra.

  //Devolvemos función ayuda
  if(memcmp("help",temporal_command,4)==0){
      printf("**************************************\n");
      printf("**        Comandos Aceptados        **\n");
      printf("**************************************\n");
      printf("help: Lista Comandos disponibles\n");
      command_index = 0;

      while (cli_command_list[command_index].key[0] != 0) {
	  printf("%s: %s\n",cli_command_list[command_index].key,cli_command_list[command_index].description);
	   command_index++;
      }
      printf("**************************************\n");
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
void cli_processing_task(void *argument)
{
  uint8_t new_char     = 0;
  uint8_t command_size = 0;
  uint8_t temporal_command[20];

  App_Message *app_message = NULL;

  for(;;)
  {
    osStatus_t  os_status;
    // TODO 8: Esperar hasta recibir un caracter de la cola char_queue que almacenaremos en la variable new_char
    os_status = osMessageQueueGet(char_queueHandle, &new_char,NULL,osWaitForever);
    if (os_status == osOK){
      // TODO 9: Almacenar el caracter en el array temporal_command hasta recibir el '\n'
      //         es conveniente contar el número de caracteres recibidos en la variable command_size
      temporal_command[command_size] = new_char;
      command_size++;

      if (new_char == '\r' && command_size > 1) {
	command_size = 0;

	// TODO 10: Reservar espacio en el Pool con osMemoryPoolAlloc
	app_message = osMemoryPoolAlloc(command_MemPool,0U);

	// TODO 11: Procesar la cadena recibida en una función a la que le pasamos la cadena y el puntero al espacio de
	//          Memoria reservado en el Pool
	process_cli_command(temporal_command, app_message);

	// TODO 12: Enviar el mensaje generado por la funcion anterior a la cola de mensajes para el Modelo.
	osMessageQueuePut(app_msg_queueHandle, &app_message, 0U, 0U);

      }

      //Check si desborda el buffer
      if(command_size>=(19)){
	  printf("Error cli_processing_task buffer desbordado");
	  command_size = 0;
      }
    } else {
	printf("Error reading the queue on cli processing task");
    }
  }
}


/*
 * command.c
 *
 *  Created on: 30 abr. 2021
 *      Author: edavidfs
 */

#include "main.h"
#include "command.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>  // Para el printf
#include <stdlib.h>


#define UNKNOWN_CLI_COMMAND {0,0,0,"Comando desconocido",(void*)unknown_cli_cmd }
#define CAM_TEMP_CLI_COMMAND {"cam temp" , CLI_CAM_TEMP_CODE , 0, "Temperatura de la cámara", (void*)cam_temp_cli_cmd}


extern UART_HandleTypeDef huart1;

void cam_temp_cli_cmd(void);
void cam_frame_cli_cmd(void);



CLI_Command cli_command_list[] = {
    CAM_TEMP_CLI_COMMAND,
    {"cam frame", CLI_CAM_FRAME_CODE, 0, "Matriz de temperatura de la cámara", (void*)cam_frame_cli_cmd},
    UNKNOWN_CLI_COMMAND
};

void cam_temp_cli_cmd(void){

  printf("Solicitar datos Temperatura\r\n");
}

void cam_frame_cli_cmd(void){
  printf("Solicitar datos de la Matriz de temperatura\r\n");
}

void unknown_cli_cmd(void){

  printf("Comando desconocido\r\n");
}

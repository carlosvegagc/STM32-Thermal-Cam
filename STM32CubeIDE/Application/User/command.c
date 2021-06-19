/*
 *  Created on: 25/05/2021
 *      Author: Carlos Vega García
 * Description: This file creates the vector with the definition of
 * 				all the implemented commands .
 *
 */


#include "main.h"
#include "command.h"


#define UNKNOWN_CLI_COMMAND {0,0,0,"Comando desconocido"}

#define CAM_TEMP_CLI_COMMAND {"Camera temp" , CLI_CAM_TEMP_CODE , 0, "Temperatura de la cámara."}
#define CAM_FRAME_COMMAND {"Camera image", CLI_CAM_FRAME_CODE, 0, "Matriz de valores de temperatura de la cámara."}
#define CAM_RAW_COMMAND {"Camera raw", CLI_CAM_RAW_CODE, 0, "Matriz de valores en crudo obtenidos de la cámara."}

#define CAM_RATE_COMMAND {"Camera rate", CLI_CAM_RATE_CODE, 1, "Actualiza frecuencia actualización cámara."}

#define CAM_ON_COMMAND {"Camera on", CLI_CAM_ON_CODE, 0, "Muestra la imagen de la cámara en pantalla."}
#define CAM_OFF_COMMAND {"Camera off", CLI_CAM_OFF_CODE, 0, "Oculta la imagen de la cámara en pantalla."}



CLI_Command cli_command_list[] = {
    CAM_TEMP_CLI_COMMAND,
	CAM_FRAME_COMMAND,
	CAM_RAW_COMMAND,
	CAM_RATE_COMMAND,
	CAM_ON_COMMAND,
	CAM_OFF_COMMAND,
    UNKNOWN_CLI_COMMAND
};


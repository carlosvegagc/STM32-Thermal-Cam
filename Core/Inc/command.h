/*
 * command.h
 */

#ifndef APPLICATION_USER_COMMAND_H_
#define APPLICATION_USER_COMMAND_H_

#define CLI_UNKNOWN_CODE    0
#define CLI_HELP_CODE       1
#define CLI_CAM_TEMP_CODE   2
#define CLI_CAM_FRAME_CODE  3
#define CLI_CAM_RAW_CODE	4
#define CLI_CAM_RATE_CODE  	5
#define CLI_CAM_ON_CODE		6
#define CLI_CAM_OFF_CODE	7

#define APP_UNKNOWN_COMMAND 0
#define APP_HELP_COMMAND    1
#define APP_SEND_CAM_TEMP   2
#define APP_SEND_CAM_FRAME  3
#define APP_SEND_CAM_RAW	4
#define APP_SEND_CAM_RATE  	5
#define APP_SEND_CAM_ON		6
#define APP_SEND_CAM_OFF	7

typedef void *(SFPointer)(void);

typedef struct{
  char *key;                  /**< cadena de caracteres que describe al comando */
  int command_code;           /**< Codigo identificativo del comando */
  int has_parameter;          /**< 1 si posee datos adicionales 0 si no */
  char *description;          /**< Descripción del comando mostrado al solicitar la ayuda */
} CLI_Command;


/** @brief  Mensaje interno de la Aplicación.
 *          Esta estructura representa los comandos que realiza la aplicación.
 *          El Modelo recibe estos mensajes desde la cola de entrada y los procesa
 */
typedef struct{
    int8_t  message_code;   /**< Código del mensaje */
    uint8_t data[20];       /**< Atributos */
}App_Message;

extern CLI_Command cli_command_list[];

#endif /* APPLICATION_USER_COMMAND_H_ */

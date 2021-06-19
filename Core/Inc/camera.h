/*
 * camera.h
 *
 *  Created on: 19 abr. 2021
 *      Author: edavidfs
 */

#ifndef APPLICATION_USER_CAMERA_H_
#define APPLICATION_USER_CAMERA_H_

#include "stm32f4xx_hal.h"

#define PIXELS_NUMBER 64

#define CAM_X_PIXELS 8
#define CAM_Y_PIXELS 8

//GLOBAL BUFFER FOR THE CAMERA FRAME
float g_frame_buffer[PIXELS_NUMBER];

//GLOBAL BUFFFER FOR THE RAW CAMERA FRAME
uint16_t g_raw_frame_buffer[PIXELS_NUMBER];


#endif /* APPLICATION_USER_CAMERA_H_ */

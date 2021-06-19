#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include <cmath>

#define STEP_PIX 25
#define FPS_TICKS 10

extern "C"
{
  #include "command.h"
  #include "cli.h"
  #include "camera.h"

  extern osMessageQueueId_t temp_queueHandle;
  extern osMessageQueueId_t cpu_temp_quequeHandle;
  extern osMessageQueueId_t app_msg_queueHandle;
  extern osMessageQueueId_t frameRate_queueHandle;
  extern osMemoryPoolId_t command_MemPool;
  extern osSemaphoreId_t frameSemHandle;
  extern osEventFlagsId_t updateBitmapHandle;
  extern osEventFlagsId_t eventButtonPressedHandle;
  extern osMutexId_t usart1MUTEXHandle;

}


Model::Model() : modelListener(0)
{

}

void Model::tick()
{


	osStatus_t os_status;

	App_Message *app_message = NULL;

	/**** UPDATE FPS ***/
	//Check if we have to calculate the FPS
    if(ticks_until_read<= 0){

		uint32_t currentTick = osKernelGetTickCount();

		fps = (1.0 / (float)(currentTick - last_tick))*100;
		fps = fps * FPS_TICKS;

		last_tick = currentTick;
		ticks_until_read = FPS_TICKS;

    }else {
    	ticks_until_read--;
    }
	this->modelListener->setFPS(fps);


	/**** UPDATE FRAME ***/
	uint32_t flag = osEventFlagsWait(updateBitmapHandle, 0x00000001U, osFlagsWaitAny, 0);
	if (flag == 1)
	{
		float cursorTemp;

		//Acquire the semaphore for access the global frame buffer
		if (osSemaphoreAcquire(frameSemHandle, 100) == osOK){

			//Copy the global
			memcpy(local_frame_buffer, g_frame_buffer, sizeof(float)*PIXELS_NUMBER);

		}

		//Release the semaphore
		osSemaphoreRelease(frameSemHandle);

		this->modelListener->updateFrame(local_frame_buffer,CAM_X_PIXELS,CAM_Y_PIXELS);

		//Calc for obtaining the mid temp value in the center of the image
		cursorTemp = (local_frame_buffer[28] + local_frame_buffer[29] + local_frame_buffer[36] + local_frame_buffer[7]) / 4;

		this->modelListener->setCursorTemperature(cursorTemp);

	}

	/**** EVENT BUTTON PHYSICAL PRESSED ***/
	flag = osEventFlagsWait(eventButtonPressedHandle, 0x00000001U, osFlagsWaitAny, 0);
	if (flag == 1)
	{
		this->sendImageUART();
	}

	/**** UPDATE TEMP CAMERA ***/
	os_status = osMessageQueueGet (temp_queueHandle, &sensorTemperature, 0, 0);
	if (os_status == osOK)
	{
	  this->sensorTemperature = sensorTemperature;
	  this->modelListener->setSensorTemperature(sensorTemperature);
	}

	/**** UPDATE CPU TEMP ***/
	os_status = osMessageQueueGet (cpu_temp_quequeHandle, &cpuTemperature, 0, 0);
	if (os_status == osOK)
	{
	  this->cpuTemperature = cpuTemperature;
	  this->modelListener->setCPUTemperature(cpuTemperature);
	}

	/**** PROCESS INCOMING COMMAND ***/
	os_status = osMessageQueueGet (app_msg_queueHandle, &app_message, NULL, 0);
	if (os_status == osOK)
	{

		this->processCMD(app_message);

		// Liberar el espacio de memoria del POOL de memoria mediante osMemoryPoolFree()
		if (osMemoryPoolFree (command_MemPool, (void*) app_message) != osOK)
		{
		  printf ("Error liberando memory pool \n\r");
		}

		app_message = NULL;

	 }

	osDelay(5);


}

//Function for processing the incoming command
void Model::processCMD(App_Message *app_message){
	 switch (app_message->message_code)
	 {
		case APP_SEND_CAM_TEMP:
		{

			if (osMutexAcquire(usart1MUTEXHandle, 100) == osOK)
			{
				printf ("CAM TEMPERATURE: %f\n", sensorTemperature);
			}

			//Release the mutex
			osMutexRelease(usart1MUTEXHandle);
			break;
		}
		case APP_SEND_CAM_FRAME:
		{
			this->sendImageUART();
			break;
		}
		case APP_SEND_CAM_RAW:
			//Acquire the semaphore for access the USART
			if (osMutexAcquire(usart1MUTEXHandle, 100) == osOK)
			{
				//Read the image from the global buffer
				printf ("CAM FRAME: ");
				//Acquire the semaphore for access the global frame buffer
				osSemaphoreAcquire (frameSemHandle, 100);

				//Send each pixel by the serial port
				for (int i = 0; i < PIXELS_NUMBER; i++)
				{
				  printf("%2d ",g_raw_frame_buffer[i]);
				}

				//Release the semaphore for access the global frame buffer
				osSemaphoreRelease (frameSemHandle);

				printf ("\n");
			}
			//Release the mutex
			osMutexRelease(usart1MUTEXHandle);

			break;

		case APP_SEND_CAM_RATE:
		{
			int newFR = atoi((const char *)(app_message->data));

			if(newFR>0){

				//Acquire the semaphore for access the USART
				if (osMutexAcquire(usart1MUTEXHandle, 100) == osOK)
				{
					printf("Updated frame rate to %d\n",newFR);
				}
				//Release the mutex
				osMutexRelease(usart1MUTEXHandle);

				this->updateSettingsValues((uint8_t)newFR,this->maxTemp,this->minTemp);
			}else{

				//Acquire the semaphore for access the USART
				if (osMutexAcquire(usart1MUTEXHandle, 100) == osOK)
				{
					printf("Error en el parámetro\n");
					printf((const char *)app_message->data);
					printf("; APP MESSAGE DATA\n");
				}

				//Release the mutex
				osMutexRelease(usart1MUTEXHandle);

			}
			break;
		}
		case APP_SEND_CAM_ON:
		{
			this->modelListener->showCamera();
			break;
		}
		case APP_SEND_CAM_OFF:
		{
			this->modelListener->hideCamera();
			break;
		}
	 }

	 return;

}

//Update the Model values and sends a message by the queue to update the frame rate of the camera.
void Model::updateSettingsValues(uint8_t frameRate,int16_t maxTemp,int16_t minTemp){
	this->maxTemp = maxTemp;
	this->minTemp = minTemp;
	this->frameRate = frameRate;

	osMessageQueuePut(frameRate_queueHandle, (void*) &(this->frameRate), 0, 0);

}

//Getter of the settings values in the model
void Model::getSettingsValues(uint8_t * frameRate,int16_t * maxTemp,int16_t * minTemp){
	*maxTemp = this->maxTemp;
	*minTemp = this->minTemp;
	*frameRate = this->frameRate;

}

//Function for sending the current frame by the UART
void Model::sendImageUART(){

	//Acquire the semaphore for access the USART
	if (osMutexAcquire(usart1MUTEXHandle, 1000) == osOK)
	{
		//Read the image from the global buffer
		printf ("CAM FRAME: ");
		//Acquire the semaphore for access the global frame buffer
		osSemaphoreAcquire (frameSemHandle, 100);

		//Send each pixel by the serial port
		for (int i = 0; i < PIXELS_NUMBER; i++)
		{
		  printf("%2.2f ",g_frame_buffer[i]);
		}

		//Release the semaphore for access the global frame buffer
		osSemaphoreRelease (frameSemHandle);

		printf ("\n");
	}


	//Release the mutex
	osMutexRelease(usart1MUTEXHandle);

}



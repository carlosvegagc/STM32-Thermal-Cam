#ifndef MODEL_HPP
#define MODEL_HPP

#include "stm32f4xx_hal.h"
#include "cmsis_os2.h"

#include <string.h>
#include <stdio.h>

extern "C"
{
  #include "command.h"
  #include "cli.h"
}

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    //Model functions for recieving upadtes of the config parameters
    void updateSettingsValues(uint8_t frameRate,int16_t maxTemp,int16_t minTemp);

    void getSettingsValues(uint8_t * frameRate,int16_t * maxTemp,int16_t * minTemp);

    void processCMD(App_Message *app_message);

    void sendImageUART();

protected:
    ModelListener* modelListener;

    float sensorTemperature;
    float cpuTemperature;

    int16_t minTemp = 20;
    int16_t maxTemp = 35;
    uint8_t frameRate = 10;

    float local_frame_buffer[64];

    uint8_t ticks_until_read = 10;
    uint32_t last_tick;
    float fps;



};

#endif // MODEL_HPP

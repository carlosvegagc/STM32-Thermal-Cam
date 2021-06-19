#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

#include <stdio.h>

#include "cmsis_os2.h"

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }

    virtual void setSensorTemperature(float temperature){  }
    virtual void setCPUTemperature(float temperature){  }
    //Function for updating the fps on the bar
    virtual void setFPS(float fps){}

    virtual void setCursorTemperature(float temperature){  }

    virtual void updateFrame(float * image, uint16_t width, uint16_t height){}

    virtual void showCamera(){}
    virtual void hideCamera(){}


    virtual void updateSettingsValues(uint8_t frameRate,int16_t maxTemp,int16_t minTemp){
    	model->updateSettingsValues(frameRate,maxTemp,minTemp);
    }

    virtual void getSettingsValues(uint8_t * frameRate,int16_t * maxTemp,int16_t * minTemp){
    	model->getSettingsValues(frameRate,maxTemp,minTemp);
    }

    virtual void sendImageUART(){
    	model->sendImageUART();
    }



protected:
    Model* model;
};

#endif // MODELLISTENER_HPP

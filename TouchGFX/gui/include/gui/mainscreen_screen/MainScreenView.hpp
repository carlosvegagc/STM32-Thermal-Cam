#ifndef MAINSCREENVIEW_HPP
#define MAINSCREENVIEW_HPP

#include <gui_generated/mainscreen_screen/MainScreenViewBase.hpp>
#include <gui/mainscreen_screen/MainScreenPresenter.hpp>

class MainScreenView : public MainScreenViewBase
{
public:
    MainScreenView();
    virtual ~MainScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    //Function for updating the sensor temp
    void setSensorTemperature(float newTemperature);

    //Function for updating the cpu temp
    void setCPUTemperature(float newTemperature);

    //Function for updating the frame
    void updateFrame(float * image, uint16_t width, uint16_t height);

    //Function for updating the cursor temp
    void setCursorTemperature(float newTemperature);

    void setFPS(float fps);

    //Functions for the visibility of the image
    void showCamera();
    void hideCamera();

    //Functions for handle the click button events
    void handle_Play_Button();
    void handle_Stop_Button();
    void handle_Picture_Button();
    void handle_Temp_Button();


protected:

    //Float for saving the sensor Temp
    float sensorTemp;

    //Float for saving the cpu Temp
    float cpuTemp;

    uint8_t frameRate = 10;
    int16_t maxTemp = 60;
    int16_t minTemp = 60;
};

#endif // MAINSCREENVIEW_HPP

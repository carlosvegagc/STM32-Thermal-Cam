#ifndef SETTINGSSCREENVIEW_HPP
#define SETTINGSSCREENVIEW_HPP

#include <gui_generated/settingsscreen_screen/SettingsScreenViewBase.hpp>
#include <gui/settingsscreen_screen/SettingsScreenPresenter.hpp>

class SettingsScreenView : public SettingsScreenViewBase
{
public:
    SettingsScreenView();
    virtual ~SettingsScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    //Function for updating the sensor temp on the bar
    void setSensorTemperature(float newTemperature);

    //Function for upadting the cpu temp on the bar
    void setCPUTemperature(float temperature);

    void setFPS(float fps);

    //Functions for handle the button touch events
    void handle_Add_FrameRate();
    void handle_Add_MaxTemp();
    void handle_Add_MinTemp();
    void handle_Min_FrameRate();
    void handle_Min_MaxTemp();
    void handle_Min_MinTemp();

protected:
    //Float for saving the sensor Temp
    float sensorTemp;

    //Float for saving the cpu Temp
    float cpuTemp;

    uint8_t frameRate = 10;
    int16_t maxTemp = 60;
    int16_t minTemp = 60;
};

#endif // SETTINGSSCREENVIEW_HPP

#include <gui/containers/TopBar.hpp>

TopBar::TopBar()
{

}

void TopBar::initialize()
{
    TopBarBase::initialize();
}

/**
 * @brief Function for updating temperature on the bar.
 * @param temperature (FLOAT)
 */
void TopBar::updateSensorTemperature(float temperature)
{
    Unicode::snprintfFloat(this->text_sensor_tempBuffer, sizeof(this->text_sensor_tempBuffer), "%4.1f", temperature);
    this->text_sensor_temp.resizeToCurrentText();
}

/**
 * @brief Function for updating the CPU temperature on the bar.
 * @param temperature (FLOAT)
 */
void TopBar::updateCPUTemperature(float temperature)
{
    Unicode::snprintfFloat(this->text_cpu_tempBuffer, sizeof(this->text_cpu_tempBuffer), "%4.1f", temperature);
    this->text_cpu_temp.resizeToCurrentText();
}


/**
 * @brief Function for updating the FPS on the bar.
 * @param fps (FLOAT)
 */
void TopBar::updateFPS(float fps)
{
    Unicode::snprintfFloat(this->text_fpsBuffer, sizeof(this->text_fpsBuffer), "%4.1f", fps);
    this->text_fps.resizeToCurrentText();
}

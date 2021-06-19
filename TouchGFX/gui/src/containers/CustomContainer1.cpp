 #include <gui/containers/CustomContainer1.hpp>

CustomContainer1::CustomContainer1()
{

}

void CustomContainer1::initialize()
{
    CustomContainer1Base::initialize();
}

/**
 * @brief Function for updating temperature on the bar.
 * @param temperature (FLOAT)
 */
void CustomContainer1::setSensorTemperature(float temperature)
{
    Unicode::snprintfFloat(this->text_sensor_tempBuffer, sizeof(this->text_sensor_tempBuffer));
    this->text_sensor_temp.resizeToCurrentText();
}

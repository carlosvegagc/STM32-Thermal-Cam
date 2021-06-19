/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/TopBarBase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>

TopBarBase::TopBarBase()
{
    setWidth(240);
    setHeight(24);
    box1.setPosition(0, 0, 238, 24);
    box1.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));

    text_cpu_temp.setXY(7, 6);
    text_cpu_temp.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    text_cpu_temp.setLinespacing(0);
    Unicode::snprintf(text_cpu_tempBuffer, TEXT_CPU_TEMP_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID3).getText());
    text_cpu_temp.setWildcard(text_cpu_tempBuffer);
    text_cpu_temp.resizeToCurrentText();
    text_cpu_temp.setTypedText(touchgfx::TypedText(T_SINGLEUSEID2));

    text_sensor_temp.setXY(85, 6);
    text_sensor_temp.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    text_sensor_temp.setLinespacing(0);
    Unicode::snprintf(text_sensor_tempBuffer, TEXT_SENSOR_TEMP_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID5).getText());
    text_sensor_temp.setWildcard(text_sensor_tempBuffer);
    text_sensor_temp.resizeToCurrentText();
    text_sensor_temp.setTypedText(touchgfx::TypedText(T_SINGLEUSEID4));

    text_fps.setXY(197, 6);
    text_fps.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    text_fps.setLinespacing(0);
    Unicode::snprintf(text_fpsBuffer, TEXT_FPS_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID7).getText());
    text_fps.setWildcard(text_fpsBuffer);
    text_fps.resizeToCurrentText();
    text_fps.setTypedText(touchgfx::TypedText(T_SINGLEUSEID6));

    add(box1);
    add(text_cpu_temp);
    add(text_sensor_temp);
    add(text_fps);
}

void TopBarBase::initialize()
{

}


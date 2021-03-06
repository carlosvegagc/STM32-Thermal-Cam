/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef TOPBARBASE_HPP
#define TOPBARBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class TopBarBase : public touchgfx::Container
{
public:
    TopBarBase();
    virtual ~TopBarBase() {}
    virtual void initialize();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box box1;
    touchgfx::TextAreaWithOneWildcard text_cpu_temp;
    touchgfx::TextAreaWithOneWildcard text_sensor_temp;
    touchgfx::TextAreaWithOneWildcard text_fps;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXT_CPU_TEMP_SIZE = 5;
    touchgfx::Unicode::UnicodeChar text_cpu_tempBuffer[TEXT_CPU_TEMP_SIZE];
    static const uint16_t TEXT_SENSOR_TEMP_SIZE = 5;
    touchgfx::Unicode::UnicodeChar text_sensor_tempBuffer[TEXT_SENSOR_TEMP_SIZE];
    static const uint16_t TEXT_FPS_SIZE = 5;
    touchgfx::Unicode::UnicodeChar text_fpsBuffer[TEXT_FPS_SIZE];

private:

};

#endif // TOPBARBASE_HPP

#ifndef TOPBAR_HPP
#define TOPBAR_HPP

#include <gui_generated/containers/TopBarBase.hpp>

class TopBar : public TopBarBase
{
public:
    TopBar();
    virtual ~TopBar() {}

    virtual void initialize();

    void updateSensorTemperature(float temperature);
    void updateCPUTemperature(float temperature);
    void updateFPS(float fps);
protected:
};

#endif // TOPBAR_HPP

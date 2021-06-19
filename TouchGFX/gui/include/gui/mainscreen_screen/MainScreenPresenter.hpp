#ifndef MAINSCREENPRESENTER_HPP
#define MAINSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class MainScreenView;

class MainScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    MainScreenPresenter(MainScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~MainScreenPresenter() {};

    //Function for updating the sensor temp
    void setSensorTemperature(float temperature);

    //Function for updating the cpu  temp
    void setCPUTemperature(float temperature);

    //Function for updating the fps on the bar
    void setFPS(float fps);

    //Function for updating the cursor temp
    void setCursorTemperature(float newTemperature);

    //Functions for the visibility of the image
    void showCamera();
    void hideCamera();

    void updateFrame(float * image, uint16_t width, uint16_t height);

private:
    MainScreenPresenter();

    MainScreenView& view;
};

#endif // MAINSCREENPRESENTER_HPP

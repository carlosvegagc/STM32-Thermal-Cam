/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef MAINSCREENVIEWBASE_HPP
#define MAINSCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/mainscreen_screen/MainScreenPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TiledImage.hpp>
#include <touchgfx/containers/buttons/Buttons.hpp>
#include <gui/containers/TopBar.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class MainScreenViewBase : public touchgfx::View<MainScreenPresenter>
{
public:
    MainScreenViewBase();
    virtual ~MainScreenViewBase() {}
    virtual void setupScreen();

    /*
     * Virtual Action Handlers
     */
    virtual void handle_Play_Button()
    {
        // Override and implement this function in MainScreen
    }

    virtual void handle_Picture_Button()
    {
        // Override and implement this function in MainScreen
    }

    virtual void handle_Temp_Button()
    {
        // Override and implement this function in MainScreen
    }

    virtual void handle_Stop_Button()
    {
        // Override and implement this function in MainScreen
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::TiledImage background;
    touchgfx::Box box1;
    touchgfx::TiledImage image_camera;
    touchgfx::ImageButtonStyle< touchgfx::ClickButtonTrigger > button_play;
    touchgfx::ImageButtonStyle< touchgfx::ClickButtonTrigger > button_picture;
    touchgfx::ImageButtonStyle< touchgfx::ClickButtonTrigger > button_temp;
    touchgfx::ImageButtonStyle< touchgfx::ClickButtonTrigger > button_settings;
    TopBar top_bar;
    touchgfx::ImageButtonStyle< touchgfx::ClickButtonTrigger > button_stop;
    touchgfx::Image img_cursor;
    touchgfx::TextAreaWithOneWildcard textCursorTemp;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTCURSORTEMP_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textCursorTempBuffer[TEXTCURSORTEMP_SIZE];

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<MainScreenViewBase, const touchgfx::AbstractButtonContainer&> flexButtonCallback;

    /*
     * Callback Handler Declarations
     */
    void flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src);

};

#endif // MAINSCREENVIEWBASE_HPP
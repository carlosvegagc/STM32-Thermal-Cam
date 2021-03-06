/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/mainscreen_screen/MainScreenViewBase.hpp>
#include <touchgfx/Color.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>

MainScreenViewBase::MainScreenViewBase() :
    flexButtonCallback(this, &MainScreenViewBase::flexButtonCallbackHandler)
{

    __background.setPosition(0, 0, 240, 320);
    __background.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));

    background.setBitmap(touchgfx::Bitmap(BITMAP_BLUE_TEXTURES_CARBON_FIBRE_ID));
    background.setPosition(0, 0, 240, 320);
    background.setOffset(0, 0);

    box1.setPosition(0, 263, 240, 57);
    box1.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));

    image_camera.setBitmap(touchgfx::Bitmap(BITMAP_DARK_BACKGROUNDS_MAIN_BG_PORTRAIT_TEXTURE_272X480PX_ID));
    image_camera.setPosition(8, 32, 224, 224);
    image_camera.setVisible(false);
    image_camera.setOffset(0, 0);

    button_play.setBitmaps(Bitmap(BITMAP_PLAY_CIRCLE_FILLED_ROUND_38PX_ID), Bitmap(BITMAP_PLAY_CIRCLE_FILLED_ROUND_38PX_ID));
    button_play.setBitmapXY(0, 0);
    button_play.setPosition(70, 273, 39, 37);
    button_play.setAction(flexButtonCallback);

    button_picture.setBitmaps(Bitmap(BITMAP_CAMERA_ID), Bitmap(BITMAP_CAMERA_ID));
    button_picture.setBitmapXY(0, 0);
    button_picture.setPosition(130, 273, 40, 37);
    button_picture.setAction(flexButtonCallback);

    button_temp.setBitmaps(Bitmap(BITMAP_TARGET_32PX_ID), Bitmap(BITMAP_TARGET_32PX_ID));
    button_temp.setBitmapXY(4, 3);
    button_temp.setPosition(189, 273, 40, 37);
    button_temp.setAction(flexButtonCallback);

    button_settings.setBitmaps(Bitmap(BITMAP_BLUE_ICONS_SETTINGS_32_ID), Bitmap(BITMAP_BLUE_ICONS_SETTINGS_32_ID));
    button_settings.setBitmapXY(2, 2);
    button_settings.setPosition(17, 275, 32, 32);
    button_settings.setAction(flexButtonCallback);

    top_bar.setXY(0, 0);

    button_stop.setBitmaps(Bitmap(BITMAP_STOP_CIRCLE_ROUND_38PX_ID), Bitmap(BITMAP_STOP_CIRCLE_ROUND_38PX_ID));
    button_stop.setBitmapXY(0, 0);
    button_stop.setPosition(70, 273, 39, 37);
    button_stop.setVisible(false);
    button_stop.setAction(flexButtonCallback);

    img_cursor.setXY(110, 134);
    img_cursor.setVisible(false);
    img_cursor.setBitmap(touchgfx::Bitmap(BITMAP_TARGET_20PX_ID));

    textCursorTemp.setXY(86, 222);
    textCursorTemp.setVisible(false);
    textCursorTemp.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    textCursorTemp.setLinespacing(0);
    Unicode::snprintf(textCursorTempBuffer, TEXTCURSORTEMP_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID23).getText());
    textCursorTemp.setWildcard(textCursorTempBuffer);
    textCursorTemp.resizeToCurrentText();
    textCursorTemp.setTypedText(touchgfx::TypedText(T_SINGLEUSEID22));

    add(__background);
    add(background);
    add(box1);
    add(image_camera);
    add(button_play);
    add(button_picture);
    add(button_temp);
    add(button_settings);
    add(top_bar);
    add(button_stop);
    add(img_cursor);
    add(textCursorTemp);
}

void MainScreenViewBase::setupScreen()
{
    top_bar.initialize();
}

void MainScreenViewBase::flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src)
{
    if (&src == &button_play)
    {
        //Interaction_Play_Button
        //When button_play clicked call virtual function
        //Call handle_Play_Button
        handle_Play_Button();
    }
    else if (&src == &button_picture)
    {
        //Interaction_Picture_Button
        //When button_picture clicked call virtual function
        //Call handle_Picture_Button
        handle_Picture_Button();
    }
    else if (&src == &button_temp)
    {
        //Interaction_Temp_Button
        //When button_temp clicked call virtual function
        //Call handle_Temp_Button
        handle_Temp_Button();
    }
    else if (&src == &button_settings)
    {
        //InteractionGoSettings
        //When button_settings clicked change screen to SettingsScreen
        //Go to SettingsScreen with screen transition towards West
        application().gotoSettingsScreenScreenCoverTransitionWest();
    }
    else if (&src == &button_stop)
    {
        //Interaction_Stop_Button
        //When button_stop clicked call virtual function
        //Call handle_Stop_Button
        handle_Stop_Button();
    }
}

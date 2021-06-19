#include <gui/settingsscreen_screen/SettingsScreenView.hpp>
#include <stdio.h>

SettingsScreenView::SettingsScreenView()
{

}

void SettingsScreenView::setupScreen()
{
    SettingsScreenViewBase::setupScreen();

    //Get the current settings values
    this->presenter->getSettingsValues(&frameRate,&maxTemp,&minTemp);

    //Update the initial values of the widgets
	Unicode::snprintf(textFPSBuffer, sizeof(this->textFPSBuffer), "%d", this->frameRate);
	this->textFPS.resizeToCurrentText();
	this->textFPS.invalidate();

	Unicode::snprintf(textMaxTempBuffer, sizeof(this->textMaxTempBuffer), "%d", this->maxTemp);
	this->textMaxTemp.resizeToCurrentText();
	this->textMaxTemp.invalidate();

	Unicode::snprintf(textMinTempBuffer, sizeof(this->textMinTempBuffer), "%d", this->minTemp);
	this->textMinTemp.resizeToCurrentText();
	this->textMinTemp.invalidate();
}

void SettingsScreenView::tearDownScreen()
{
    SettingsScreenViewBase::tearDownScreen();

    //Update the global settings values
	this->presenter->updateSettingsValues(frameRate,maxTemp,minTemp);
}

void SettingsScreenView::setSensorTemperature(float newTemperature)
{
	sensorTemp = newTemperature;
	top_bar.updateSensorTemperature(sensorTemp);
	top_bar.invalidate();
}

void SettingsScreenView::setCPUTemperature(float newTemperature)
{
	cpuTemp = newTemperature;
	top_bar.updateCPUTemperature(cpuTemp);
	top_bar.invalidate();
}


void SettingsScreenView::setFPS(float fps)
{
	top_bar.updateFPS(fps);
	top_bar.invalidate();
}

void SettingsScreenView::handle_Add_FrameRate(){
	frameRate = frameRate + 1;


	//Update the value on the widget
	Unicode::snprintf(textFPSBuffer, sizeof(this->textFPSBuffer), "%2d", this->frameRate);
	this->textFPS.resizeToCurrentText();
	this->textFPS.invalidate();

}
void SettingsScreenView::handle_Add_MaxTemp(){
	maxTemp = maxTemp + 5;

	//Update the value on the widget
	Unicode::snprintf(textMaxTempBuffer, sizeof(this->textMaxTempBuffer), "%2d", this->maxTemp);
	this->textMaxTemp.resizeToCurrentText();
	this->textMaxTemp.invalidate();

}
void SettingsScreenView::handle_Add_MinTemp(){
	minTemp = minTemp + 5;

	//Update the value on the widget
	Unicode::snprintf(textMinTempBuffer, sizeof(this->textMinTempBuffer), "%2d", this->minTemp);
	this->textMinTemp.resizeToCurrentText();
	this->textMinTemp.invalidate();
}
void SettingsScreenView::handle_Min_FrameRate(){
	frameRate = frameRate - 1;

	//Update the value on the widget
	Unicode::snprintf(textFPSBuffer, sizeof(this->textFPSBuffer), "%2d", this->frameRate);
	this->textFPS.resizeToCurrentText();
	this->textFPS.invalidate();


}
void SettingsScreenView::handle_Min_MaxTemp(){
	maxTemp = maxTemp - 5;

	//Update the value on the widget
	Unicode::snprintf(textMaxTempBuffer, sizeof(this->textMaxTempBuffer), "%2d", this->maxTemp);
	this->textMaxTemp.resizeToCurrentText();
	this->textMaxTemp.invalidate();

}
void SettingsScreenView::handle_Min_MinTemp(){
	minTemp = minTemp - 5;

	//Update the value on the widget
	Unicode::snprintf(textMinTempBuffer, sizeof(this->textMinTempBuffer), "%2d", this->minTemp);
	this->textMinTemp.resizeToCurrentText();
	this->textMinTemp.invalidate();


}

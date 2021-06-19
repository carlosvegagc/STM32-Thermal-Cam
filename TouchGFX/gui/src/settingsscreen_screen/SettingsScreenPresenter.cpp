#include <gui/settingsscreen_screen/SettingsScreenView.hpp>
#include <gui/settingsscreen_screen/SettingsScreenPresenter.hpp>

SettingsScreenPresenter::SettingsScreenPresenter(SettingsScreenView& v)
    : view(v)
{

}

void SettingsScreenPresenter::activate()
{

}

void SettingsScreenPresenter::deactivate()
{

}

void SettingsScreenPresenter::setSensorTemperature(float temperature){
	this->view.setSensorTemperature(temperature);
}


void SettingsScreenPresenter::setCPUTemperature(float temperature){
	this->view.setCPUTemperature(temperature);
}


void SettingsScreenPresenter::setFPS(float fps){
	this->view.setFPS(fps);
}



#include <gui/mainscreen_screen/MainScreenView.hpp>
#include <gui/mainscreen_screen/MainScreenPresenter.hpp>

MainScreenPresenter::MainScreenPresenter(MainScreenView& v)
    : view(v)
{

}

void MainScreenPresenter::activate()
{

}

void MainScreenPresenter::deactivate()
{

}

void MainScreenPresenter::setSensorTemperature(float temperature){
	this->view.setSensorTemperature(temperature);
}

void MainScreenPresenter::setCPUTemperature(float temperature){
	this->view.setCPUTemperature(temperature);
}

void MainScreenPresenter::setFPS(float fps){
	this->view.setFPS(fps);
}


void MainScreenPresenter::updateFrame(float * image, uint16_t width, uint16_t height){
	this->view.updateFrame(image,width,height);
}

void MainScreenPresenter::showCamera(){
	this->view.showCamera();
}

void MainScreenPresenter::hideCamera(){
	this->view.hideCamera();
}

//Function for updating the cursor temp
void MainScreenPresenter::setCursorTemperature(float newTemperature){
	this->view.setCursorTemperature(newTemperature);
}

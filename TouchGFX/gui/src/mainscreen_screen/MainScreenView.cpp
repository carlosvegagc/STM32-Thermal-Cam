#include <gui/mainscreen_screen/MainScreenView.hpp>

#include <stdio.h>
#include <string.h>

#include "cmsis_os2.h"

#define STEP_PIX 28

#define BMP_WIDTH 224
#define BMP_HEIGHT 224

BitmapId bmp;

MainScreenView::MainScreenView()
{

}

void MainScreenView::setupScreen()
{
    MainScreenViewBase::setupScreen();

    //Get the current settings values
    this->presenter->getSettingsValues(&frameRate,&maxTemp,&minTemp);


	//GENERATE IMAGE
	uint16_t *psram = (uint16_t*) (0xd0000000 + 240 * 320 * 2 * 2);

	Bitmap::setCache(psram,320 * 1024,1);
	bmp = Bitmap::dynamicBitmapCreate(BMP_WIDTH,
										BMP_WIDTH,
										Bitmap::L8,
										Bitmap::CLUT_FORMAT_L8_RGB888);
	image_camera.setBitmap(Bitmap(bmp));

	uint8_t *data = Bitmap::dynamicBitmapGetAddress(image_camera.getBitmap());

	//1 byte pr pixel, round up to 32-bit
	uint32_t byteSize = BMP_WIDTH*BMP_HEIGHT;
	byteSize = ((byteSize + 3) & ~3);

	//Palette starts four bytes after the pixels
	uint8_t* color_table = (data + byteSize + 4);

	//** Generates the Color Table **
	uint8_t separator_A = (uint8_t)(minTemp/0.3125);
	uint8_t separator_E = (uint8_t)(maxTemp/0.3125);

	//printf("Limit Values: %d - %d\n",separator_E,separator_A);

	uint8_t separator_C = (separator_E-separator_A)/2 + separator_A;
	//uint8_t separator_D = (separator_E-separator_C)/2 + separator_C;
	uint8_t separator_B = (separator_C-separator_A)/2 + separator_A;

	uint8_t dist = separator_A;
	uint8_t m = 256/ dist;

	uint16_t pos = 0;

	for(int i = 0; i < dist; i++){
		color_table[pos*3 + 0] = 255 ;
		color_table[pos*3 + 1] = 0x00;
		color_table[pos*3 + 2] = 0x00;
		pos++;
	}

	dist = separator_B-separator_A;
	m = 256/ dist;

	for(int i = 0; i < dist; i++){
		color_table[pos*3 + 0] = 255;
		color_table[pos*3 + 1] = m*i;
		color_table[pos*3 + 2] = 0x00;
		pos++;
	}

	for(int i = 0; i < dist; i++){
		color_table[pos*3 + 0] = 255-i*m;
		color_table[pos*3 + 1] = 255;
		color_table[pos*3 + 2] = 0x00;
		pos++;
	}

	for(int i = 0; i < dist; i++){
		color_table[pos*3 + 0] = 0x00;
		color_table[pos*3 + 1] = 255;
		color_table[pos*3 + 2] = m*i;
		pos++;
	}

	for(int i = 0; i < dist; i++){
		color_table[pos*3 + 0] = 0x00;
		color_table[pos*3 + 1] = 255-i*m;
		color_table[pos*3 + 2] = 255;
		pos++;
	}


	dist = 255-separator_E;
	for(int i = 0; i < dist; i++){
		color_table[pos*3 + 0] = 0x00;
		color_table[pos*3 + 1] = 0x00;
		color_table[pos*3 + 2] = 255;
		pos++;
	}

	//printf("Final pos = %d\n",pos);

}

void MainScreenView::tearDownScreen()
{
    MainScreenViewBase::tearDownScreen();
    Bitmap::dynamicBitmapDelete(bmp);
}

void MainScreenView::setSensorTemperature(float newTemperature)
{
	sensorTemp = newTemperature;
	top_bar.updateSensorTemperature(sensorTemp);
	top_bar.invalidate();
}

void MainScreenView::setCPUTemperature(float newTemperature)
{
	cpuTemp = newTemperature;
	top_bar.updateCPUTemperature(cpuTemp);
	top_bar.invalidate();
}

void MainScreenView::setFPS(float fps)
{
	top_bar.updateFPS(fps);
	top_bar.invalidate();
}

void MainScreenView::setCursorTemperature(float newTemperature)
{
	Unicode::snprintfFloat(this->textCursorTempBuffer, sizeof(this->textCursorTempBuffer), "%4.2f", newTemperature);
    this->textCursorTemp.resizeToCurrentText();
    textCursorTemp.invalidate();
}



void MainScreenView::updateFrame(float * image, uint16_t width, uint16_t height)
{

	uint8_t *data = Bitmap::dynamicBitmapGetAddress(image_camera.getBitmap());
	uint32_t byteSize = BMP_WIDTH*BMP_HEIGHT;

	uint16_t step_x = BMP_WIDTH / width;
	uint16_t step_y = BMP_HEIGHT / height;

	uint8_t * pointer = data;
	uint16_t pos = 0;
	for (int y = 0; y < height; y++){
		uint8_t * line_pointer = pointer;
		for (int x = 0; x < width; x++){
			uint8_t pixValue = (uint8_t)((float)(image[pos]/(float)0.3125));
			//uint8_t pixValue = (uint8_t)((float)(0/0.3125));
			memset(pointer,pixValue,step_x);
			pointer = pointer + step_x;
			pos++;
		}

		//Copiamos la línea superior para rellenar las posiciones hasta la próxima línea.
		for(int lines = 0; lines < (step_y-1); lines++){
			memcpy(pointer,line_pointer,BMP_WIDTH);
			pointer = pointer + BMP_WIDTH;
		}
	}



    image_camera.invalidate();


}

void MainScreenView::handle_Play_Button(){
	this->showCamera();
}

void MainScreenView::handle_Stop_Button(){
	this->hideCamera();
}

void MainScreenView::showCamera(){
	image_camera.setVisible(true);
	image_camera.invalidate();
	button_play.setVisible(false);
	button_play.setTouchable(false);
	button_play.invalidate();
	button_stop.setVisible(true);
	button_stop.setTouchable(true);
	button_stop.invalidate();
}

void MainScreenView::hideCamera(){
	image_camera.setVisible(false);
	image_camera.invalidate();
	button_play.setVisible(true);
	button_play.setTouchable(true);
	button_play.invalidate();
	button_stop.setVisible(false);
	button_stop.setTouchable(false);
	button_stop.invalidate();
}


void MainScreenView::handle_Picture_Button(){
	//Call the function in the model for sending the image by the UART
	this->presenter->sendImageUART();

}
void MainScreenView::handle_Temp_Button(){
	if(img_cursor.isVisible()){
		img_cursor.setVisible(false);
		textCursorTemp.setVisible(false);
	}else{
		img_cursor.setVisible(true);
		textCursorTemp.setVisible(true);
	}


}

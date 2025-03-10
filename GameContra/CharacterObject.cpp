#include "stdafx.h"
#include "CharacterObject.h"
MainObject::MainObject() {
	frame_ = 0;
	x_pos_ = 0;
	y_pos_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;
	status_ = -1; // chưa biết trạng thái sang trái hay sang phải 

}
MainObject::~MainObject() {

}
bool MainObject::LoadImg(std::string path, SDL_Renderer* screen) {
	bool ret = BaseObject::LoadImg(path, screen);
}
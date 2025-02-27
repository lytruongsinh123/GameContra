#include "stdafx.h"
#include "BaseObject.h"
#include "BaseFunction.h"

// Định nghĩa Contructor
BaseObject::BaseObject() {
	p_object_ = NULL;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
}

BaseObject::~BaseObject() {
	Free();
}

// Dinh nghia ham LoadImg
bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen) {
	SDL_Texture* new_texture = NULL;

	SDL_Surface* load_surface = IMG_Load(path.c_str()); // Dua surface thanh texture
	if (load_surface != NULL) {
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B)); // Xoa background cua hinh anh nhan vat
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface); // Tao texture tu surface 
		if (new_texture != NULL) { // Gan gia tri cho rect
			rect_.w = load_surface->w;
			rect_.h = load_surface->h;
		}
		SDL_FreeSurface(load_surface); // Xoa surface
	}
	p_object_ = new_texture; // Gan texture cho p_object

	return p_object_ != NULL; // Neu p_object khac NULL thi return true
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip /* = NULL */) { 
	SDL_Rect renderquad = { rect_.x, rect_.y, rect_.w, rect_.h }; // Dinh vi tri va kich thuoc cua hinh anh
	SDL_RenderCopy(des, p_object_, clip, &renderquad); 
}

void BaseObject::Free() { // Xoa hinh anh
	if(p_object_ !=NULL) {
		SDL_DestroyTexture(p_object_);
		p_object_ = NULL;
		rect_.w = 0;
		rect_.h = 0;
	}
}
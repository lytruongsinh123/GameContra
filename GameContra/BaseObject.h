// Image
// Description: BaseObject class is the base class for all objects in the game. It contains the basic attributes and methods for objects in the game.

#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "BaseFunction.h"
#include <SDL.h>
#include <string>

class BaseObject {
public:
	BaseObject(); // Constructor
	~BaseObject(); // Destructor
	void SetRect(const int& x, const int& y) { // Set kich thuoc cho hinh anh
		rect_.x = x;
		rect_.y = y;
	}
	SDL_Rect GetRect() const { return rect_; } // Lay kich thuoc cua hinh anh
	SDL_Texture* GetObject() const { return p_object_; } // Lay hinh anh

	virtual bool LoadImg(const std::string path, SDL_Renderer* screen); // Load hinh anh tu file len man hinh
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL); // Hien thi
	void Free();
protected:
	SDL_Texture* p_object_; // luu tru hinh anh
	SDL_Rect rect_; // luu tru kich thuoc cua hinh anh
};

#endif // BASE_OBJECT_H_

#ifndef GEOMETRIC_H_
#define GEOMETRIC_H_
#include "BaseFunction.h"

typedef struct GeometricFormat { // hình dạng của hình
public :
	GeometricFormat(int left, int top, int width, int height) { left_ = left, top_ = top, width_ = width, height_ = height; };
	int left_ ;
	int top_;
	int width_;
	int height_;
};
typedef struct ColorData {
	ColorData(Uint8 r, Uint8 b, Uint8 g) { red_ = r, green_ = g, blue_ = b; }
public:
	Uint8 red_;
	Uint8 green_;
	Uint8 blue_;
};
class Geometric { // đối tượng để vẽ
public:
	static void RenderRectangle(const GeometricFormat& geo_size, const ColorData& color_data, SDL_Renderer* screen); // vẽ hình chữ nhật
	static void RenderOutline(const GeometricFormat& geo_size, const ColorData& color_data, SDL_Renderer* screen);
};
#endif
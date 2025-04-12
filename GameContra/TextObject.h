#ifndef TEXT_OBJECT_H
#define TEXT_OBJECT_H
#include "BaseFunction.h"

class TextObject {
public:
	TextObject();
	~TextObject();
	enum TextColor {
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		BLACK_TEXT = 2,
		YELLOW_TEXT = 3,
		GREEN_TEXT = 4,
	};
	bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen); // đầu vào là font chữ và renderer để hiện chữ
	void Free();
	void SetColor(Uint8 red, Uint8 green, Uint8 blue); // set màu sắc cho chữ
	void SetColor(int type); // set màu sắc cho chữ
	void RenderText(SDL_Renderer* screen, 
		            int x_pos, int y_pos, 
		            SDL_Rect* clip = NULL, 
		            double angle = 0.0, 
		            SDL_Point* center = NULL, 
		            SDL_RendererFlip flip = SDL_FLIP_NONE); // hiện chữ
	int GetWidth() const { return width_; } // lấy chiều rộng của chữ
	int GetHeight() const { return height_; } // lấy chiều cao của chữ
	void SetText(const std::string& text) { str_val_ = text; } // set nội dung của chữ
	std::string GetText() const { return str_val_; } // lấy nội dung của chữ
private:
	std::string str_val_; // lưu nội dung của text
	SDL_Color text_color_; // màu sắc của text
	SDL_Texture* texture_; // quản lý text
	int width_; // chiều rộng của text
	int height_; // chiều cao của text
};
#endif
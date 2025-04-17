 #include "stdafx.h"
#include "TextObject.h"
TextObject::TextObject() {
	texture_ = NULL;
	text_color_.r = 255;
	text_color_.g = 255;
	text_color_.b = 255;
	width_ = 0;
	height_ = 0;
}

TextObject::~TextObject(){
	cout << "Free TextObject" << endl;
	Free(); // giải phóng texture
}
bool TextObject::LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen) {
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_val_.c_str(), text_color_); // tạo bề mặt chữ
	if (text_surface != NULL) {
		texture_ = SDL_CreateTextureFromSurface(screen, text_surface);
		if (texture_ != NULL) {
			width_ = text_surface->w; // lấy chiều rộng của chữ
			height_ = text_surface->h; // lấy chiều cao của chữ
		}
		SDL_FreeSurface(text_surface); // giải phóng bề mặt chữ
	}
	return texture_ != NULL;
}
void TextObject::Free() {
	if (texture_ != NULL) {
		SDL_DestroyTexture(texture_); // giải phóng texture
		texture_ = NULL;
	}
}
void TextObject::SetColor(Uint8 red, Uint8 green, Uint8 blue) { // set màu sắc cho chữ
	text_color_.r = red;
	text_color_.g = green;
	text_color_.b = blue;
}
void TextObject::SetColor(int type) { // set màu sắc cho chữ
	if (type == RED_TEXT) {
		SDL_Color color = { 255, 0, 0 };
		text_color_ = color;
	}
	else if (type == WHITE_TEXT) {
		SDL_Color color = { 255, 255, 255 };
		text_color_ = color;
	}
	else if (type == BLACK_TEXT) {
		SDL_Color color = { 0, 0, 0 };
		text_color_ = color;
	}
	else if (type == YELLOW_TEXT) {
		SDL_Color color = { 255, 255, 0 };
		text_color_ = color;
	}
	else if (type == GREEN_TEXT) {
		SDL_Color color = { 0, 255, 0 };
		text_color_ = color;
	}
}
void TextObject::RenderText(SDL_Renderer* screen,
	int x_pos, int y_pos,
	SDL_Rect* clip,
	double angle,
	SDL_Point* center,
	SDL_RendererFlip flip) { // hiện chữ trên màn hình
	SDL_Rect render_quad = { x_pos, y_pos, width_, height_ }; // tạo hình chữ nhật để hiện chữ
	if (clip != NULL) {
		render_quad.w = clip->w; // lấy chiều rộng của clip
		render_quad.h = clip->h; // lấy chiều cao của clip
	}
	SDL_RenderCopyEx(screen, texture_, clip, &render_quad, angle, center, flip); // hiện chữ
}
// Load nội dung qua hàm LoadFromRenderText qua font nội dung màu sắc được truyền vào hàm
// Tạo một surface từ nội dung và màu sắc font
// Convert surface thành texture
// Lấy chiều rộng và chiều cao của texture
// Giải phóng surface
// Trả về true nếu texture khác NULL
// Trả về false nếu texture NULL
// Free hàm giải phóng texture
// Nếu texture khác NULL thì giải phóng texture
// Set màu sắc cho chữ
// Set màu sắc cho chữ dựa vào kiểu truyền vào
// Nếu kiểu là RED_TEXT thì set màu đỏ
// Nếu kiểu là WHITE_TEXT thì set màu trắng
// Nếu kiểu là BLACK_TEXT thì set màu đen
// Nếu kiểu là YELLOW_TEXT thì set màu vàng
// Nếu kiểu là GREEN_TEXT thì set màu xanh lá
// Rồi show lên màn hình
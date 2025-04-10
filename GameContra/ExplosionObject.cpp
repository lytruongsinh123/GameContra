#include "stdafx.h"
#include "ExplosionObject.h"

ExplosionObject::ExplosionObject() {
	frame_ = 0;
	frame_width_ = 0;
	frame_height_ = 0;
}

ExplosionObject::~ExplosionObject() {

}

bool ExplosionObject::LoadImg(std::string path, SDL_Renderer* screen) {
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret) {
		frame_width_ = rect_.w / 8; // chiều rộng của 1 frame
		frame_height_ = rect_.h; // chiều cao của 1 frame
	}
	return ret;
}

void ExplosionObject::set_clip() {  // trạng thái từng frame của nhân vật
	if (frame_width_ > 0 && frame_height_ > 0) {
		frame_clip_[0].x = 0;  // lấy frame đầu tiên của nhân vật ở vị trí x = 0
		frame_clip_[0].y = 0;  // lấy frame đầu tiên của nhân vật ở vị trí y = 0
		frame_clip_[0].w = frame_width_;  //kích thước của frame nhân vật
		frame_clip_[0].h = frame_height_;

		frame_clip_[1].x = frame_width_; // lấy frame thứ 2 ở vị trí x = width_frame_
		frame_clip_[1].y = 0;  // lấy frame thứ 2 ở vị trí y = 0
		frame_clip_[1].w = frame_width_;  
		frame_clip_[1].h = frame_height_;

		frame_clip_[2].x = 2 * frame_width_;
		frame_clip_[2].y = 0;
		frame_clip_[2].w = frame_width_;
		frame_clip_[2].h = frame_height_;

		frame_clip_[3].x = 3 * frame_width_;
		frame_clip_[3].y = 0;
		frame_clip_[3].w = frame_width_;
		frame_clip_[3].h = frame_height_;

		frame_clip_[4].x = 4 * frame_width_;
		frame_clip_[4].y = 0;
		frame_clip_[4].w = frame_width_;
		frame_clip_[4].h = frame_height_;

		frame_clip_[5].x = 5 * frame_width_;
		frame_clip_[5].y = 0;
		frame_clip_[5].w = frame_width_;
		frame_clip_[5].h = frame_height_;

		frame_clip_[6].x = 6 * frame_width_;
		frame_clip_[6].y = 0;
		frame_clip_[6].w = frame_width_;
		frame_clip_[6].h = frame_height_;

		frame_clip_[7].x = 7 * frame_width_;
		frame_clip_[7].y = 0;
		frame_clip_[7].w = frame_width_;
		frame_clip_[7].h = frame_height_;
	}
}

void ExplosionObject::Show(SDL_Renderer* screen) {
	SDL_Rect* current_clip = &frame_clip_[frame_]; // lấy frame hiện tại của nhân vật
	SDL_Rect render_quad = { rect_.x, rect_.y, frame_width_, frame_height_ }; // chứa tọa độ và kích thước của nhân vật
	if (current_clip != NULL) {
		render_quad.w = current_clip->w;
		render_quad.h = current_clip->h;
	}

	SDL_RenderCopy(screen, p_object_, current_clip, &render_quad);
}
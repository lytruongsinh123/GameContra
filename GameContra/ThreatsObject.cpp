#include "stdafx.h"
#include "ThreatsObject.h"

ThreatsObject::ThreatsObject() // Hàm khởi tạo object ThreatsObject, ban đầu các hệ số = 0
{
	width_frame_ = 0;
	height_frame_ = 0;
	x_val_ = 0.0;
	y_val_ = 0.0;
	x_pos_ = 0.0;
	y_pos_ = 0.0;
	on_ground_ = 0;
	come_back_time_ = 0;
	frame_ = 0;

}

ThreatsObject::~ThreatsObject() // hủy object
{

}

bool ThreatsObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen); // chạy load img từ Base Object trước, kiểm tra xem load oke ch
	if (ret)
	{
		width_frame_ = rect_.w / THREAT_FRAME_NUM;
		height_frame_ = rect_.h;
	}

	return ret;
}

void ThreatsObject::set_clips() // xây dựng clips cho threat object
{
	for (int i = 0; i <= 7; ++i)
	{
		frame_clip_[i].x = i * width_frame_;
		frame_clip_[i].y = 0;
		frame_clip_[i].w = width_frame_;
		frame_clip_[i].h = height_frame_;
	}
}

void ThreatsObject::Show(SDL_Renderer* des)
{
	if (come_back_time_ == 0) // chỉ lúc come_back_time_ == 0 thì mới hiển thị
	{
		rect_.x = x_pos_ - map_x_;
		rect_.y = y_pos_ - map_y_;
		frame_++; // tăng liên tục frame lên, khác với nhân vật chỉ ấn button thì mới tăng frame, tăng frame thì nhân vật di chuyển tại chỗ
		if (frame_ >= 8)
		{
			frame_ = 0; // set up frame về như ban đầu
		}


        SDL_Rect* currentClip = &frame_clip_[frame_];
		SDL_Rect rendQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
		SDL_RenderCopy(des, p_object_, currentClip, &rendQuad);
	}
}

void ThreatsObject::DoPlayer(Map& gMap) // hàm thể hiện những gì threat sẽ phản ứng khi bị player tác động (cụ thể là die)
{
	if (come_back_time_ == 0)
	{
		x_val_ = 0;
		y_val_ += THREAT_GRAVITY_SPEED; // thay đổi giá trị y thể hiện khi vật thể rơi xuống
		if (y_val_ >= THREAT_MAX_FALL_SPEED)
		{
			y_val_ = THREAT_MAX_FALL_SPEED; //nếu vận tốc phương y đạt giá trị max thì không tăng nữa (chắc để ko bị corrupt frame)
		}

		CheckToMap(gMap); // kéo threats theo bản đồ, tức là dịch chuyển threats á má
	}
	else if (come_back_time_ > 0)
	{
		come_back_time_--;
		if (come_back_time_ == 0)
		{
			x_val_ = 0;
			y_val_ = 0;
			if (x_pos_ > 256)
			{
				x_pos_ -= 256; // ko rơi xuống vực
			}
			else
			{
				x_pos_ = 0;
			}
			y_pos_ = 0;
			come_back_time_ = 0;
		}
	}
}


void ThreatsObject::CheckToMap(Map& gMap) // đã giải thích trong hàm main
{
	int x1 = 0; // giới hạn kiểm tra từ A đến B theo chiều x 
	int x2 = 0;
	int y1 = 0; // giới hạn kiểm tra từ A đến B theo chiều y
	int y2 = 0;

	//kiểm tra theo chiều ngang
	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

	x1 = (x_pos_ + x_val_) / TILE_SIZE; // x1 là vị trí của nhân vật chia cho kích thước của ô vuông
	x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE; // x2 là vị trí của nhân vật + chiều rộng của nhân vật - 1 (vì sai số) chia cho kích thước của ô vuông

	y1 = (y_pos_) / TILE_SIZE;
	y2 = (y_pos_ + height_min - 1) / TILE_SIZE;


	/*
	   x1, y1 ******** x2, y1
	   *
	   *
	   *
	   x1, y2 ******** x2,y2

	*/
	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (x_val_ > 0) {// nhân  vật đang di chuyển qua phải
			int val1 = gMap.tile[y1][x2]; // lấy giá trị của ô vật phẩm mà nhân vật sẽ va chạm
			int val2 = gMap.tile[y2][x2];
			if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY))
			{
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= (width_frame_ + 1);
				x_val_ = 0;
			}

			else if (x_val_ < 0) { // nhân vật di chuyển qua trái 
				int val1 = gMap.tile[y1][x1]; // lấy giá trị của ô vật phẩm mà nhân vật sẽ va chạm
				int val2 = gMap.tile[y2][x1];
				if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY))
				{
					x_pos_ = (x1 + 1) * TILE_SIZE;
					x_val_ = 0;
				}
			}
		}

		//Check theo chiều dọc
		int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
		x1 = (x_pos_) / TILE_SIZE;
		x2 = (x_pos_ + width_min) / TILE_SIZE;

		y1 = (y_pos_ + y_val_) / TILE_SIZE;
		y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
			if (y_val_ > 0) { // nhân vật rơi xuống
				int val1 = gMap.tile[y2][x1];
				int val2 = gMap.tile[y2][x2];
				if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY))
				{
					y_pos_ = y2 * TILE_SIZE;
					y_pos_ -= (height_frame_ + 1);
					y_val_ = 0;
					on_ground_ = true;
				}
			}
			else if (y_val_ < 0) { // nhân vật nhảy lên
				int val1 = gMap.tile[y1][x1];
				int val2 = gMap.tile[y1][x2];
				if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY))
				{
					y_pos_ = (y1 + 1) * TILE_SIZE;
					y_val_ = 0;
				}
				/*if (gMap.tile[y1][x1] != BLANK_TILE || gMap.tile[y1][x2] != BLANK_TILE) {
					y_pos_ = (y1 + 1) * TILE_SIZE;
					y_val_ = 0;
				}*/
			}
		}

		x_pos_ += x_val_;
		y_pos_ += y_val_;
		if (x_pos_ < 0) { // lùi đến đít bản đồ thì dùng lại
			x_pos_ = 0;
		}
		else if (x_pos_ + width_frame_ > gMap.max_X_) { // quá giới hạn bản đồ thì dùng lại
			x_pos_ = gMap.max_X_ - width_frame_ - 1;
		}
		if (y_pos_ > gMap.max_Y_) {
			come_back_time_ = 60; // thời gian quay trở lại độ trễ 60
		}
	}
}

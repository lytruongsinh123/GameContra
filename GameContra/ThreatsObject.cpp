#include "stdafx.h"
#include "ThreatsObject.h"

ThreatsObject::ThreatsObject() // Hàm khởi tạo object ThreatsObject, ban đầu các hệ số = 0
{
	width_frame_ = 0;
	height_frame_ = 0;
	x_val_ = 0.0;
	y_val_ = 0.0;
	x_pos_ = 0;
	y_pos_ = 0;
	on_ground_ = 0;
	come_back_time_ = 0;
	frame_ = 0;
	animation_a_ = 0;
	animation_b_ = 0;
	input_type_.left_ = 0;
	type_move_ = STATIC_THREAT; // mặc định là đứng yên
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
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		frame_clip_[0].x = 0;
		frame_clip_[0].y = 0;
		frame_clip_[0].w = width_frame_;
		frame_clip_[0].h = height_frame_;

		frame_clip_[1].x = width_frame_;
		frame_clip_[1].y = 0;
		frame_clip_[1].w = width_frame_;
		frame_clip_[1].h = height_frame_;

		frame_clip_[2].x = width_frame_ * 2;
		frame_clip_[2].y = 0;
		frame_clip_[2].w = width_frame_;
		frame_clip_[2].h = height_frame_;

		frame_clip_[3].x = width_frame_ * 3;
		frame_clip_[3].y = 0;
		frame_clip_[3].w = width_frame_;
		frame_clip_[3].h = height_frame_;

		frame_clip_[4].x = width_frame_ * 4;
		frame_clip_[4].y = 0;
		frame_clip_[4].w = width_frame_;
		frame_clip_[4].h = height_frame_;

		frame_clip_[5].x = width_frame_ * 5;
		frame_clip_[5].y = 0;
		frame_clip_[5].w = width_frame_;
		frame_clip_[5].h = height_frame_;

		frame_clip_[6].x = width_frame_ * 6;
		frame_clip_[6].y = 0;
		frame_clip_[6].w = width_frame_;
		frame_clip_[6].h = height_frame_;

		frame_clip_[7].x = width_frame_ * 7;
		frame_clip_[7].y = 0;
		frame_clip_[7].w = width_frame_;
		frame_clip_[7].h = height_frame_;
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
		if(input_type_.left_ == 1) {
			x_val_ -= THREAT_SPEED; // di chuyển qua trái
		}
		else if (input_type_.right_ == 1)
		{
			x_val_ += THREAT_SPEED; // di chuyển qua phải
		}


		CheckToMap(gMap); // kéo threats theo bản đồ, tức là dịch chuyển threats á má
	}
	if (come_back_time_ > 0)
	{
		come_back_time_--;
		if (come_back_time_ == 0)
		{
			InitThreats(); // khởi tạo lại threat
		}
	}
}

void ThreatsObject::InitThreats() // khởi tạo threat
{
	x_val_ = 0;
	y_val_ = 0;
	if (x_pos_ > 256)
	{
		x_pos_ -= 256; // ko rơi xuống vực
		// cho khoảng di chuyển lùi lại
		animation_a_ -= 256;
		animation_b_ -= 256;
	}
	else
	{
		x_pos_ = 0;
	}
	y_pos_ = 0;
	come_back_time_ = 0;
	input_type_.left_ = 1;
}
//void ThreatsObject::CheckToMap(Map& gMap) // đã giải thích trong hàm main
//{
//	int x1 = 0; // giới hạn kiểm tra từ A đến B theo chiều x 
//	int x2 = 0;
//	int y1 = 0; // giới hạn kiểm tra từ A đến B theo chiều y
//	int y2 = 0;
//
//	//kiểm tra theo chiều ngang
//	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;
//
//	x1 = (x_pos_ + x_val_) / TILE_SIZE; // x1 là vị trí của nhân vật chia cho kích thước của ô vuông
//	x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE; // x2 là vị trí của nhân vật + chiều rộng của nhân vật - 1 (vì sai số) chia cho kích thước của ô vuông
//
//	y1 = (y_pos_) / TILE_SIZE;
//	y2 = (y_pos_ + height_min - 1) / TILE_SIZE;
//
//
//	/*
//	   x1, y1 ******** x2, y1
//	   *
//	   *
//	   *
//	   x1, y2 ******** x2,y2
//
//	*/
//	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
//		if (x_val_ > 0) {// nhân  vật đang di chuyển qua phải
//			int val1 = gMap.tile[y1][x2]; // lấy giá trị của ô vật phẩm mà nhân vật sẽ va chạm
//			int val2 = gMap.tile[y2][x2];
//			if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY))
//			{
//				x_pos_ = x2 * TILE_SIZE;
//				x_pos_ -= (width_frame_ + 1);
//				x_val_ = 0;
//			}
//
//			else if (x_val_ < 0) { // nhân vật di chuyển qua trái 
//				int val1 = gMap.tile[y1][x1]; // lấy giá trị của ô vật phẩm mà nhân vật sẽ va chạm
//				int val2 = gMap.tile[y2][x1];
//				if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY))
//				{
//					x_pos_ = (x1 + 1) * TILE_SIZE;
//					x_val_ = 0;
//				}
//			}
//		}
//
//		//Check theo chiều dọc
//		int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
//		x1 = (x_pos_) / TILE_SIZE;
//		x2 = (x_pos_ + width_min) / TILE_SIZE;
//
//		y1 = (y_pos_ + y_val_) / TILE_SIZE;
//		y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;
//
//		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
//			if (y_val_ > 0) { // nhân vật rơi xuống
//				int val1 = gMap.tile[y2][x1];
//				int val2 = gMap.tile[y2][x2];
//				if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY))
//				{
//					y_pos_ = y2 * TILE_SIZE;
//					y_pos_ -= (height_frame_ + 1);
//					y_val_ = 0;
//					on_ground_ = true;
//				}
//			}
//			else if (y_val_ < 0) { // nhân vật nhảy lên
//				int val1 = gMap.tile[y1][x1];
//				int val2 = gMap.tile[y1][x2];
//				if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY))
//				{
//					y_pos_ = (y1 + 1) * TILE_SIZE;
//					y_val_ = 0;
//				}
//			}
//		}
//
//		x_pos_ += x_val_;
//		y_pos_ += y_val_;
//		if (x_pos_ < 0) { // lùi đến đít bản đồ thì dùng lại
//			x_pos_ = 0;
//		}
//		else if (x_pos_ + width_frame_ > gMap.max_X_) { // quá giới hạn bản đồ thì dùng lại
//			x_pos_ = gMap.max_X_ - width_frame_ - 1;
//		}
//		cout << y_pos_ << " " << gMap.max_Y_  << endl;
//		if (y_pos_  > gMap.max_Y_) {
//			come_back_time_ = 60; // thời gian quay trở lại độ trễ 60
//		}
//	}
//}

void ThreatsObject::CheckToMap(Map& gMap) {
	int x1 = 0; // giới hạn kiểm tra từ A đến B theo chiều x 
	int x2 = 0;
	int y1 = 0; // giới hạn kiểm tra từ A đến B theo chiều y
	int y2 = 0;

	// kiểm tra theo chiều ngang
	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

	x1 = (x_pos_ + x_val_) / TILE_SIZE; // x1 là vị trí của nhân vật chia cho kích thước của ô vuông
	x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE; // x2 là vị trí của nhân vật + chiều rộng của nhân vật - 1 (vì sai số) chia cho kích thước của ô vuông

	y1 = (y_pos_) / TILE_SIZE;
	y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (x_val_ > 0) { // nhân vật đang di chuyển qua phải
			int val1 = gMap.tile[y1][x2]; // lấy giá trị của ô vật phẩm mà nhân vật sẽ va chạm
			int val2 = gMap.tile[y2][x2];
			if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY)) {
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= (width_frame_ + 1);
				x_val_ = 0;
			}
		}
		else if (x_val_ < 0) { // nhân vật di chuyển qua trái 
			int val1 = gMap.tile[y1][x1]; // lấy giá trị của ô vật phẩm mà nhân vật sẽ va chạm
			int val2 = gMap.tile[y2][x1];
			if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY)) {
				x_pos_ = (x1 + 1) * TILE_SIZE;
				x_val_ = 0;
			}
		}
	}

	// Check theo chiều dọc
	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
	x1 = (x_pos_) / TILE_SIZE;
	x2 = (x_pos_ + width_min) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (y_val_ > 0) { // nhân vật rơi xuống
			int val1 = gMap.tile[y2][x1];
			int val2 = gMap.tile[y2][x2];
			if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY)) {
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= (height_frame_ + 1);
				y_val_ = 0;
				on_ground_ = true;
			}
		}
		else if (y_val_ < 0) { // nhân vật nhảy lên
			int val1 = gMap.tile[y1][x1];
			int val2 = gMap.tile[y1][x2];
			if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY)) {
				y_pos_ = (y1 + 1) * TILE_SIZE;
				y_val_ = 0;
			}
		}
	}

	x_pos_ += x_val_;
	y_pos_ += y_val_;

	if (x_pos_ < 0) { // lùi đến đít bản đồ thì dừng lại
		x_pos_ = 0;
	}
	else if (x_pos_ + width_frame_ > gMap.max_X_) { // quá giới hạn bản đồ thì dừng lại
		x_pos_ = gMap.max_X_ - width_frame_ - 1;
	}

	if (y_pos_ > gMap.max_Y_) {
		come_back_time_ = 60; // thời gian quay trở lại độ trễ 60
	}
}

void ThreatsObject::ImpMoveType(SDL_Renderer* screen) {
	if (type_move_ == STATIC_THREAT) {
		// do nothing
		;
	}
	else {
		if (on_ground_ == true) {
			if (x_pos_ > animation_b_) { // quá phần giới hạn bên phải sẽ quay đầu lại
				input_type_.left_ = 1;
				input_type_.right_ = 0;
				LoadImg("img//threat_left1.png", screen);
			}
			else 
				if (x_pos_ < animation_a_) { // quá phần giới hạn bên trái sẽ quay đầu lại
					input_type_.left_ = 0;
					input_type_.right_ = 1;
					LoadImg("img//threat_right1.png", screen);
				}
			
		}
		else {
			if (input_type_.left_ == 1) { // trên không trung 
				LoadImg("img//threat_left1.png", screen);
			}
			else {
				LoadImg("img//threat_right1.png", screen);
			}
		}
	}
}

void ThreatsObject::InitBullet(BulletObject* p_bullet, SDL_Renderer* screen) {
	if (p_bullet != NULL) {
		p_bullet->set_bullet_type(BulletObject::LASER_BULLET); // loại đạn
		bool ret = p_bullet->LoadImgBullet(screen); // load hình ảnh viên đạn

		if (ret) {
			p_bullet->set_is_move(true);
			p_bullet->set_bullet_dir(BulletObject::DIR_LEFT); // hướng bắn
			p_bullet->SetRect(rect_.x + 20, rect_.y + 10); // tọa độ bắn viên đạn
			p_bullet->set_x_val(10); // tốc độ bắn
			bullet_list_.push_back(p_bullet); // thêm viên đạn vào danh sách
		}
	}
}

void ThreatsObject::MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit) { // kiểm tra đạn
	for (int i = 0; i < bullet_list_.size(); i++) { 
		BulletObject* p_bullet = bullet_list_.at(i);
		if (p_bullet != NULL) {
			if (p_bullet->get_is_move()) { // kiểm tra xem viên đạn có di chuyển không
				int bullet_distance = rect_.x + width_frame_ - p_bullet->GetRect().x; // khoảng cách giữa viên đạn và nhân vật
				if (bullet_distance < 300 && bullet_distance > 0) { // nếu khoảng cách 300 pixels thì sẽ bắn
					p_bullet->HandleMove(x_limit, y_limit);
					p_bullet->Render(screen);
				}
				else {
					p_bullet->set_is_move(false); 
				}
				p_bullet->HandleMove(x_limit, y_limit); 
				p_bullet->Render(screen);
			}
			else { // nếu đạn bắn ra khỏi giới hạn thì sẽ reset lại vị trí đầu tiên nên chỉ cần 1 viên đạn
				p_bullet->set_is_move(true);
				p_bullet->SetRect(rect_.x + 20, rect_.y + 10); // dùng rec_.x và rec_.y để lấy tọa độ của viên đạn là vị trí của threat
			}
		}
	}
}

#include "stdafx.h"
#include "CharacterObject.h"
#include "SoundManager.h"

MainObject::MainObject() {
	frame_ = 0;
	x_pos_ = 0;
	y_pos_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;
	status_ = WALK_NONE; // chưa biết trạng thái sang trái hay sang phải 
	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.jump_ = 0;
	input_type_.down_ = 0;
	input_type_.up_ = 0;
	on_ground_ = false;
	map_x_ = 0;
	map_y_ = 0;
	come_back_time_ = 0;
	money_count_ = 0;
	eat_grass_Hp_ = false; // Corrected identifier
}
MainObject::~MainObject() {

}
bool MainObject::LoadImg(std::string path, SDL_Renderer* screen) {
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret == true) {
		width_frame_ = rect_.w / 8; // lấy chiều rộng của 1 frame trong ảnh
		height_frame_ = rect_.h;
	}

	return ret;
}

SDL_Rect MainObject::GetRectFrame() {
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = rect_.w / NUM_FRAME;
	rect.h = rect_.h;

	return rect;
}

void MainObject::set_clips() {  // trạng thái từng frame của nhân vật
	if (width_frame_ > 0 && height_frame_ > 0) {
		frame_clip_[0].x = 0;  // lấy frame đầu tiên của nhân vật ở vị trí x = 0
		frame_clip_[0].y = 0;  // lấy frame đầu tiên của nhân vật ở vị trí y = 0
		frame_clip_[0].w = width_frame_;  //kích thước của frame nhân vật
		frame_clip_[0].h = height_frame_;

		frame_clip_[1].x = width_frame_; // lấy frame thứ 2 ở vị trí x = width_frame_
		frame_clip_[1].y = 0;  // lấy frame thứ 2 ở vị trí y = 0
		frame_clip_[1].w = width_frame_;
		frame_clip_[1].h = height_frame_;

		frame_clip_[2].x = 2 * width_frame_;
		frame_clip_[2].y = 0;
		frame_clip_[2].w = width_frame_;
		frame_clip_[2].h = height_frame_;

		frame_clip_[3].x = 3 * width_frame_;
		frame_clip_[3].y = 0;
		frame_clip_[3].w = width_frame_;
		frame_clip_[3].h = height_frame_;

		frame_clip_[4].x = 4 * width_frame_;
		frame_clip_[4].y = 0;
		frame_clip_[4].w = width_frame_;
		frame_clip_[4].h = height_frame_;

		frame_clip_[5].x = 5 * width_frame_;
		frame_clip_[5].y = 0;
		frame_clip_[5].w = width_frame_;
		frame_clip_[5].h = height_frame_;

		frame_clip_[6].x = 6 * width_frame_;
		frame_clip_[6].y = 0;
		frame_clip_[6].w = width_frame_;
		frame_clip_[6].h = height_frame_;

		frame_clip_[7].x = 7 * width_frame_;
		frame_clip_[7].y = 0;
		frame_clip_[7].w = width_frame_;
		frame_clip_[7].h = height_frame_;
	}
}

void MainObject::Show(SDL_Renderer* des) {
	UpdateImagePlayer(des);
	if (input_type_.left_ == 1 || input_type_.right_ == 1) { // Ấn nút di chuyển trái hoặc phải
		frame_++; // tăng frame lên 1 để tạo hiệu ứng di chuyển
	}
	else {
		frame_ = 0; // nhân vật đứng yên
	}


	if (frame_ >= 8) {
		frame_ = 0; // nếu frame lớn hơn 8 thì trở về frame đầu tiên
	}
	if (come_back_time_ == 0) {
		rect_.x = x_pos_ - map_x_; // vị trí của nhân vật
		rect_.y = y_pos_ - map_y_;
		SDL_Rect* current_clip = &frame_clip_[frame_]; // lấy frame hiện tại của nhân vật

		SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ }; // chứa tọa độ và kích thước của nhân vật 

		SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
	}
}

void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen) { // hàm xử lý sự kiện
	if (events.type == SDL_KEYDOWN) { // ấn phím xuống
		switch (events.key.keysym.sym) {
		case SDLK_RIGHT:
		{
			status_ = WALK_RIGHT;
			input_type_.right_ = 1;
			input_type_.left_ = 0;
			UpdateImagePlayer(screen);
		}
		break;
		case SDLK_LEFT:
		{
			status_ = WALK_LEFT;
			input_type_.left_ = 1;
			input_type_.right_ = 0;
			UpdateImagePlayer(screen);
		}
		break;
		}
	}
	else if (events.type == SDL_KEYUP) {
		switch (events.key.keysym.sym) {
		case SDLK_RIGHT:
		{
			input_type_.right_ = 0;
		}
		break;
		case SDLK_LEFT:
		{
			input_type_.left_ = 0;
		}
		break;
		}
	}
	//if (events.type == SDL_MOUSEBUTTONDOWN) {
	//	if (events.button.button == SDL_BUTTON_RIGHT) {
	//		input_type_.jump_ = 1;
	//	}
	//	else if (events.button.button == SDL_BUTTON_LEFT) {
	//		// Tạo viên đạn mới
	//		BulletObject* p_bullet = new BulletObject();
	//		p_bullet->LoadImg("img//threat2_bullet.png", screen);
	//		
	//		if (status_ == WALK_LEFT) { // nếu nhân vật đang di chuyển sang trái
	//			p_bullet->set_bullet_dir(BulletObject::DIR_UP_LEFT); // viên đạn di chuyển sang trái
	//			p_bullet->SetRect(this->rect_.x, this->rect_.y + height_frame_ * 0.28);
	//		}
	//		else {
	//			p_bullet->set_bullet_dir(BulletObject::DIR_UP_RIGHT); // viên đạn di chuyển sang phải
	//			p_bullet->SetRect(this->rect_.x + width_frame_ - 20, this->rect_.y + height_frame_ * 0.28);
	//		}

	//		p_bullet->set_x_val(20); // tốc độ di chuyển của viên đạn
	//		p_bullet->set_y_val(20);
	//		p_bullet->set_is_move(true); // viên đạn di chuyển

	//		p_bullet_list_.push_back(p_bullet); // thêm viên đạn vào danh sách viên đạn
	//	}
	//}



	if (events.type == SDL_MOUSEBUTTONDOWN) {
		if (events.button.button == SDL_BUTTON_RIGHT) {
			input_type_.jump_ = 1;
		}
		else if (events.button.button == SDL_BUTTON_LEFT) {
			// Tạo viên đạn mới
			BulletObject* p_bullet = new BulletObject();
			p_bullet->set_bullet_type(BulletObject::SPHERE_BULLET); // Set kiểu của đạn
			bool ret = p_bullet->LoadImgBullet(screen);
			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
			bool is_up_pressed = currentKeyStates[SDL_SCANCODE_UP];
			bool is_down_pressed = currentKeyStates[SDL_SCANCODE_DOWN];
			cout << is_up_pressed << endl;
			if (is_up_pressed == 1 && is_down_pressed == 0) {
				if (status_ == WALK_LEFT) { // nếu nhân vật đang di chuyển sang trái
					p_bullet->set_bullet_dir(BulletObject::DIR_UP_LEFT); // viên đạn di chuyển sang trái
					p_bullet->SetRect(this->rect_.x, this->rect_.y + height_frame_ * 0.28);
				}
				else {
					p_bullet->set_bullet_dir(BulletObject::DIR_UP_RIGHT); // viên đạn di chuyển sang phải
					p_bullet->SetRect(this->rect_.x + width_frame_ - 20, this->rect_.y + height_frame_ * 0.28);
				}
			}
			if (is_up_pressed == 0 && is_down_pressed == 0) {
				if (status_ == WALK_LEFT) { // nếu nhân vật đang di chuyển sang trái
					p_bullet->set_bullet_dir(BulletObject::DIR_LEFT); // viên đạn di chuyển sang trái
					p_bullet->SetRect(this->rect_.x, this->rect_.y + height_frame_ * 0.28);
				}
				else {
					p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT); // viên đạn di chuyển sang phải
					p_bullet->SetRect(this->rect_.x + width_frame_ - 20, this->rect_.y + height_frame_ * 0.28);
				}
			}
			if (is_down_pressed == 1 && is_up_pressed == 0) {
				if (status_ == WALK_LEFT) { // nếu nhân vật đang di chuyển sang trái
					p_bullet->set_bullet_dir(BulletObject::DIR_DOWN_LEFT); // viên đạn di chuyển sang trái
					p_bullet->SetRect(this->rect_.x, this->rect_.y + height_frame_ * 0.28);
				}
				else {
					p_bullet->set_bullet_dir(BulletObject::DIR_DOWN_RIGHT); // viên đạn di chuyển sang phải
					p_bullet->SetRect(this->rect_.x + width_frame_ - 20, this->rect_.y + height_frame_ * 0.28);
				}
			}

			p_bullet->set_x_val(20); // tốc độ di chuyển của viên đạn
			p_bullet->set_y_val(20);
			p_bullet->set_is_move(true); // viên đạn di chuyển
			p_bullet_list_.push_back(p_bullet); // thêm viên đạn vào danh sách viên đạn
		}
	}
}

void MainObject::HandleBullet(SDL_Renderer* des) {
	for (int i = 0; i < p_bullet_list_.size(); i++) { // Kiểm tra trong băng bạn có đạn hay không
		BulletObject* p_bullet = p_bullet_list_.at(i); // lấy ra viên đạn đó
		if (p_bullet != NULL) { // kiểm tra viên đạn có khác null khôn
			if (p_bullet->get_is_move()) { // nếu viên đạn di chuyển
				p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT); // xử lý di chuyển viên đạn
				p_bullet->Render(des); // liên tục vẽ viên đạn lên màn hình
			}
			else {
				p_bullet_list_.erase(p_bullet_list_.begin() + i); // xóa viên đạn khỏi danh sách
				if (p_bullet != NULL) {
					delete p_bullet;
					p_bullet = NULL;
				}
			}
		}
	}
}
void MainObject::RemoveBullet(const int& idx) {
	int size = p_bullet_list_.size(); // kiểm tra trong băng đạn có đạn ko 
	if (size > 0 && idx < size) { // nếu có đạn và vị trí viên đạn trong băng đạn
		BulletObject* p_bullet = p_bullet_list_.at(idx); // lấy ra viên đạn đó
		p_bullet_list_.erase(p_bullet_list_.begin() + idx); // xóa viên đạn khỏi danh sách

		if (p_bullet) {
			delete p_bullet; // xóa viên đạn
			p_bullet = NULL;
		}
	}
}// xóa đạn 
void MainObject::DoPlayer(Map& map_data) {
	
	if (come_back_time_ == 0) {  // nếu thời gian comeback = 0 thì nhân vật di chuyển bình thường
		x_val_ = 0;
		y_val_ += 0.8; // tốc độ rơi
		if (y_val_ >= MAX_FALL_SPEED) {
			y_val_ = MAX_FALL_SPEED;
		}

		if (input_type_.left_ == 1) { // di chuyển sang bên trái + 1 lượng PLAYER_SPEED
			x_val_ -= PLAYER_SPEED;
		}
		else if (input_type_.right_ == 1) {
			x_val_ += PLAYER_SPEED;
		}

		if (input_type_.jump_ == 1) {
			if (on_ground_ == true) { // nếu nhân vật đang ở trên mặt đất
				y_val_ = -PLAYER_JUMP_VAL; // nhảy lêne;
			}
			on_ground_ = false;
			input_type_.jump_ = 0;
		}
		CheckToMap(map_data);
		CenterEntityOnMap(map_data);
	}
	if (come_back_time_ > 0) { // nhân vật đang ở vùng ngoài bản đồ 4 tile map
		come_back_time_--;
		if (come_back_time_ == 0) {   // Reset again
			on_ground_ = false;
			if (x_pos_ > 256) { // nếu rơi ở giữa bản đồ
				x_pos_ -= 256;
			}
			else { // nếu rơi gần điêm xuất phát
				x_pos_ = 0;
			}
			y_pos_ = 0;
			x_val_ = 0;
			y_val_ = 0;
		}
	}
}

void MainObject::CenterEntityOnMap(Map& map_data) {
	map_data.start_X_ = x_pos_ - (SCREEN_WIDTH / 2); // khi nhân vật di chuyển được 1/ 2 màn hình thì bản đồ được cuốn theo
	if (map_data.start_X_ < 0) {
		map_data.start_X_ = 0;
	}
	else if (map_data.start_X_ + SCREEN_WIDTH >= map_data.max_X_) {
		map_data.start_X_ = map_data.max_X_ - SCREEN_WIDTH;
	}


	// Di chuyển bản đồ theo chiều dọc 
	map_data.start_Y_ = y_pos_ - (SCREEN_HEIGHT / 2);
	if (map_data.start_Y_ < 0) {
		map_data.start_Y_ = 0;
	}
	else if (map_data.start_Y_ + SCREEN_HEIGHT >= map_data.max_Y_) {
		map_data.start_Y_ = map_data.max_Y_ - SCREEN_HEIGHT;
	}
}
//void MainObject::CheckToMap(Map& map_data) { // hàm chính để kiểm tra va chạm với map
//	int x1 = 0; // giới hạn kiểm tra từ A đến B theo chiều x 
//	int x2 = 0;
//
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
//			int val1 = map_data.tile[y1][x2]; // lấy giá trị của ô vật phẩm mà nhân vật sẽ va chạm
//			int val2 = map_data.tile[y2][x2];
//
//			if (val1 == STATE_MONEY || val2 == STATE_MONEY) { // nếu nhân vật va chạm với tiền
//				map_data.tile[y1][x2] = 0; // xóa tiền
//				map_data.tile[y2][x2] = 0;
//				IncreaseMoney(); // tăng tiền
//			}
//			else {
//				if (val1 != BLANK_TILE || val2 != BLANK_TILE) {
//					x_pos_ = x2 * TILE_SIZE;
//					x_pos_ -= (width_frame_ + 1);
//					x_val_ = 0;
//				}
//			}
//		}
//		else if (x_val_ < 0) { // nhân vật di chuyển qua trái 
//			int val1 = map_data.tile[y1][x1]; // lấy giá trị của ô vật phẩm mà nhân vật sẽ va chạm
//			int val2 = map_data.tile[y2][x1];
//
//			if (val1 == STATE_MONEY || val2 == STATE_MONEY) { // nếu nhân vật va chạm với tiền
//				map_data.tile[y1][x1] = 0; // xóa tiền
//				map_data.tile[y2][x1] = 0;
//				IncreaseMoney(); // tăng tiền
//			}
//			else {
//				if (val1 != BLANK_TILE || val2 != BLANK_TILE) {
//					x_pos_ = (x1 + 1) * TILE_SIZE;
//					x_val_ = 0;
//				}
//			}
//		}
//	}
//
//	//Check theo chiều dọc
//	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
//	x1 = (x_pos_) / TILE_SIZE;
//	x2 = (x_pos_ + width_min) / TILE_SIZE;
//
//	y1 = (y_pos_ + y_val_) / TILE_SIZE;
//	y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;
//
//	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
//		if (y_val_ > 0) { // nhân vật rơi xuống
//			int val1 = map_data.tile[y2][x1];
//			int val2 = map_data.tile[y2][x2];
//
//			if (val1 == STATE_MONEY || val2 == STATE_MONEY) { // nếu nhân vật va chạm với tiền
//				map_data.tile[y2][x1] = 0; // xóa tiền
//				map_data.tile[y2][x2] = 0;
//				IncreaseMoney(); // tăng tiền
//			}
//			else {
//				if (val1 != BLANK_TILE || val2 != BLANK_TILE) {
//					y_pos_ = y2 * TILE_SIZE;
//					y_pos_ -= (height_frame_ + 1);
//					y_val_ = 0;
//					on_ground_ = true;
//					if (status_ == WALK_NONE) {
//						status_ = WALK_RIGHT;
//					}
//				}
//			}
//		}
//		else if (y_val_ < 0) { // nhân vật nhảy lên
//			int val1 = map_data.tile[y1][x1];
//			int val2 = map_data.tile[y1][x2];
//			if (val1 == STATE_MONEY || val2 == STATE_MONEY) { // nếu nhân vật va chạm với tiền
//				map_data.tile[y1][x1] = 0; // xóa tiền
//				map_data.tile[y1][x2] = 0;
//				IncreaseMoney(); // tăng tiền
//			}
//			else {
//				if (val1 != BLANK_TILE || val2 != BLANK_TILE) {
//					y_pos_ = (y1 + 1) * TILE_SIZE;
//					y_val_ = 0;
//				}
//			}
//			/*if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE) {
//				y_pos_ = (y1 + 1) * TILE_SIZE;
//				y_val_ = 0;
//			}*/
//		}
//	}
//
//	x_pos_ += x_val_;
//	y_pos_ += y_val_;
//	if (x_pos_ < 0) { // lùi đến đít bản đồ thì dùng lại
//		x_pos_ = 0;
//	}
//	else if (x_pos_ + width_frame_ > map_data.max_X_) { // quá giới hạn bản đồ thì dùng lại
//		x_pos_ = map_data.max_X_ - width_frame_ - 1;
//	}
//	if (y_pos_ > map_data.max_Y_) {
//		come_back_time_ = 60; // thời gian quay trở lại độ trễ 60
//	}
//}
void MainObject::CheckToMap(Map& map_data) { // hàm chính để kiểm tra va chạm với map
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
		if (x_val_ > 0) { // nhân vật đang di chuyển qua phải
			int val1 = map_data.tile[y1][x2]; // lấy giá trị của ô vật phẩm mà nhân vật sẽ va chạm
			int val2 = map_data.tile[y2][x2];

			if (val1 == STATE_MONEY) { // nếu nhân vật va chạm với vàng
				map_data.tile[y1][x2] = 0; // xóa vàng
				IncreaseMoney(); // tăng tiền
			}
			if (val2 == STATE_MONEY) { // nếu nhân vật va chạm với vàng
				map_data.tile[y2][x2] = 0; // xóa vàng
				IncreaseMoney(); // tăng tiền
			}
			if (val1 == DRUG_HP) { // nếu nhân vật va chạm với thuốc
				map_data.tile[y1][x2] = 0; // xóa thuốc
				eat_grass_Hp_ = true; // tăng máu
			}
			if (val2 == DRUG_HP) { // nếu nhân vật va chạm với thuốc
				map_data.tile[y2][x2] = 0; // xóa thuốc
				eat_grass_Hp_ = true; // tăng máu
			}
			if (val1 != STATE_MONEY && 
				val2 != STATE_MONEY && 
				val1 != DRUG_HP && 
				val2 != DRUG_HP && 
				val1 != TREE1 && 
				val2 != TREE1 && 
				val1 != TREE3 && 
				val2 != TREE3 && 
				val1 != TREE4 && 
				val2 != TREE4 && 
				val1 != TREE5 && 
				val2 != TREE5) {
				if (val1 != BLANK_TILE || val2 != BLANK_TILE) {
					x_pos_ = x2 * TILE_SIZE;
					x_pos_ -= (width_frame_ + 1);
					x_val_ = 0;
				}
			}
		}
		else if (x_val_ < 0) { // nhân vật di chuyển qua trái 
			int val1 = map_data.tile[y1][x1]; // lấy giá trị của ô vật phẩm mà nhân vật sẽ va chạm
			int val2 = map_data.tile[y2][x1];

			if (val1 == STATE_MONEY) { // nếu nhân vật va chạm với vàng
				map_data.tile[y1][x1] = 0; // xóa vàng
				IncreaseMoney(); // tăng tiền
			}
			if (val2 == STATE_MONEY) { // nếu nhân vật va chạm với vàng
				map_data.tile[y2][x1] = 0; // xóa vàng
				IncreaseMoney(); // tăng tiền
			}
			if (val1 == DRUG_HP) { // nếu nhân vật va chạm với thuốc
				map_data.tile[y1][x1] = 0; // xóa thuốc
				eat_grass_Hp_ = true; // tăng máu
			}
			if (val2 == DRUG_HP) { // nếu nhân vật va chạm với thuốc
				map_data.tile[y2][x1] = 0; // xóa thuốc
				eat_grass_Hp_ = true; // tăng máu
			}
			if (val1 != STATE_MONEY && 
				val2 != STATE_MONEY && 
				val1 != DRUG_HP && 
				val2 != DRUG_HP && 
				val1 != TREE1 && 
				val2 != TREE1 && 
				val1 != TREE3 && 
				val2 != TREE3 && 
				val1 != TREE4 && 
				val2 != TREE4 && 
				val1 != TREE5 && 
				val2 != TREE5) {
				if (val1 != BLANK_TILE || val2 != BLANK_TILE) {
					x_pos_ = (x1 + 1) * TILE_SIZE;
					x_val_ = 0;
				}
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
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];

			if (val1 == STATE_MONEY) { // nếu nhân vật va chạm với vàng
				map_data.tile[y2][x1] = 0; // xóa vàng
				IncreaseMoney(); // tăng tiền
			}
			if (val2 == STATE_MONEY) { // nếu nhân vật va chạm với vàng
				map_data.tile[y2][x2] = 0; // xóa vàng
				IncreaseMoney(); // tăng tiền
			}
			if (val1 == DRUG_HP) { // nếu nhân vật va chạm với thuốc
				map_data.tile[y2][x1] = 0; // xóa thuốc
				eat_grass_Hp_ = true; // tăng máu
			}
			if (val2 == DRUG_HP) { // nếu nhân vật va chạm với thuốc
				map_data.tile[y2][x2] = 0; // xóa thuốc
				eat_grass_Hp_ = true; // tăng máu
			}
			if (val1 != STATE_MONEY && 
				val2 != STATE_MONEY && 
				val1 != DRUG_HP && 
				val2 != DRUG_HP && 
				val1 != TREE1 && 
				val2 != TREE1 && 
				val1 != TREE3 && 
				val2 != TREE3 && 
				val1 != TREE4 && 
				val2 != TREE4 && 
				val1 != TREE5 && 
				val2 != TREE5) {
				if (val1 != BLANK_TILE || val2 != BLANK_TILE) {
					y_pos_ = y2 * TILE_SIZE;
					y_pos_ -= (height_frame_ + 1);
					y_val_ = 0;
					on_ground_ = true;
					if (status_ == WALK_NONE) {
						status_ = WALK_RIGHT;
					}
				}
			}
		}
		else if (y_val_ < 0) { // nhân vật nhảy lên
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];
			if (val1 == STATE_MONEY) { // nếu nhân vật va chạm với vàng
				map_data.tile[y1][x1] = 0; // xóa vàng
				IncreaseMoney(); // tăng tiền
			}
			if (val2 == STATE_MONEY) { // nếu nhân vật va chạm với vàng
				map_data.tile[y1][x2] = 0; // xóa vàng
				IncreaseMoney(); // tăng tiền
			}
			if (val1 == DRUG_HP) { // nếu nhân vật va chạm với thuốc
				map_data.tile[y1][x1] = 0; // xóa thuốc
				eat_grass_Hp_ = true; // tăng máu
			}
			if (val2 == DRUG_HP) { // nếu nhân vật va chạm với thuốc
				map_data.tile[y1][x2] = 0; // xóa thuốc
				eat_grass_Hp_ = true; // tăng máu
			}
			if (val1 != STATE_MONEY && 
				val2 != STATE_MONEY && 
				val1 != DRUG_HP && 
				val2 != DRUG_HP && 
				val1 != TREE1 && 
				val2 != TREE1 && 
				val1 != TREE3 && 
				val2 != TREE3 && 
				val1 != TREE4 && 
				val2 != TREE4  && 
				val1 != TREE5 && 
				val2 != TREE5) {
				if (val1 != BLANK_TILE || val2 != BLANK_TILE) {
					y_pos_ = (y1 + 1) * TILE_SIZE;
					y_val_ = 0;
				}
			}
		}
	}

	x_pos_ += x_val_;
	y_pos_ += y_val_;
	if (x_pos_ < 0) { // lùi đến đít bản đồ thì dừng lại
		x_pos_ = 0;
	}
	else if (x_pos_ + width_frame_ > map_data.max_X_) { // quá giới hạn bản đồ thì dừng lại
		x_pos_ = map_data.max_X_ - width_frame_ - 1;
	}
	if (y_pos_ > map_data.max_Y_) {
		come_back_time_ = 60; // thời gian quay trở lại độ trễ 60
	}
}


void MainObject::IncreaseMoney() {
	money_count_++;
}
void MainObject::UpdateImagePlayer(SDL_Renderer* des) {
	if (on_ground_ == true) {
		if (status_ == WALK_LEFT) {
			LoadImg("img//player_left1.png", des);
		}
		else {
			LoadImg("img//player_right1.png", des);
		}
	}
	else {
		if (status_ == WALK_LEFT) {
			LoadImg("img//jum_left1.png", des);
		}
		else {
			LoadImg("img//jum_right1.png", des);
		}
	}
}
#include "stdafx.h"
#include "PlayPower.h"
PlayerPower::PlayerPower() {
	number_ = 0;
}
PlayerPower::~PlayerPower() {
}
void PlayerPower::AddPos(const int& pos) {
	pos_list_.push_back(pos);
}
void PlayerPower::Init(SDL_Renderer* screen) {
	LoadImg("img//player_pw.png", screen); // load hình ảnh số mạng
	number_ = 4; // mặc định là 3 mạng
	if (pos_list_.size() > 0) {
		pos_list_.clear(); // xóa danh sách vị trí
	}
	AddPos(20); // thêm vị trí đầu tiên
	AddPos(60); // thêm vị trí thứ 2
	AddPos(100); // thêm vị trí thứ 3
	AddPos(140);
}
void PlayerPower::Show(SDL_Renderer* des) {
	// show tất cả tấm ảnh theo vị trí
	// pos_list_ là danh sách các vị trí x của các mạng
	// có bao nhiêu vị trí thì show bấy nhiêu
	for (int i = 0; i < pos_list_.size(); i++) {
		rect_.x = pos_list_.at(i);
		rect_.y = 0;
		Render(des); // use des instead of screen
	}
}
void PlayerPower::InCrease() {
	number_++; // tăng số mạng lên 1
	int last_pos = pos_list_.back(); // lấy vị trí cuối cùng
	last_pos  += 40; // tăng thêm 40 pixels
	pos_list_.push_back(last_pos); // thêm vị trí mới vào danh sách
}
void PlayerPower::DeCrease() {
	number_--; // giảm số mạng đi 1
	pos_list_.pop_back(); // xóa vị trí cuối cùng
}



PlayerMoney::PlayerMoney() {
	x_pos_ = 0;
	y_pos_ = 0;
}
PlayerMoney::~PlayerMoney() {
}
void PlayerMoney::Init(SDL_Renderer* screen) {
	bool ret = LoadImg("img//money_img.png", screen); // load hình ảnh đồng tiền
}
void PlayerMoney::Show(SDL_Renderer* screen) {
	rect_.x = x_pos_;
	rect_.y = y_pos_;
	Render(screen); // use screen instead of g_screen
}
#include "stdafx.h"
#include "CharacterObject.h"
#include "BulletObject.h"

BulletObject::BulletObject() {
	x_val_ = 0;
	y_val_ = 0;
	is_move_ = false;
}
BulletObject::~BulletObject() {

}

void BulletObject::HandleMove(const int& x_border, const int& y_border) {
	if (buller_dir_ == DIR_RIGHT) { // nếu viên đạn di chuyển sang phải
		rect_.x += x_val_;
		if (rect_.x > x_border) {
			is_move_ = false;
		}
	}
	else if (buller_dir_ == DIR_LEFT) { // nếu viên đạn di chuyển sang trái
		rect_.x -= x_val_;
		if (rect_.x < 0) {
			is_move_ = false;
		}
	}
}
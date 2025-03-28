
#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_
#include "BaseObject.h"
#include "BaseFunction.h"
class BulletObject : public BaseObject {
public:
	BulletObject();
	~BulletObject();
	enum BullDir {
		DIR_RIGHT = 20,
		DIR_LEFT = 21,
		DIR_UP = 22,
		DIR_UP_LEFT = 23,
		DIR_UP_RIGHT = 24,
		DIR_DOWN_LEFT = 25,
		DIR_DOWN_RIGHT = 26,
		DIR_DOWN = 27,
	};

	enum BulletType {
		SPHERE_BULLET = 50,
		LASER_BULLET =51,
	};

	void set_x_val(const int& xVal) { x_val_ = xVal; }
	void set_y_val(const int& yVal) { y_val_ = yVal; }
	int get_x_val() const { return x_val_; } // lấy giá trị x_val_ của viên đạn
	int get_y_val() const { return y_val_; } // lấy giá trị y_val_ của viên đạn

	void set_is_move(const bool& isMove) { is_move_ = isMove; } // set trạng thái di chuyển của viên đạn
	bool get_is_move() const { return is_move_; } // lấy trạng thái di chuyển của viên đạn

	void set_bullet_dir(const unsigned int& bulletDir) { buller_dir_ = bulletDir; } // set hướng viên đạn
	unsigned int get_bullet_dir() const { return buller_dir_; } // lấy hướng viên đạn

	void set_bullet_type(const unsigned int& bulletType) { bullet_type_ = bulletType; }
	unsigned int get_bullet_type() const { return bullet_type_; }

	void HandleMove(const int& x_border, const int& y_border); // xử lý di chuyển viên đạn
	void LoadImgBullet(SDL_Renderer* des);
private:
	int x_val_; // lượng di chuyển viên đạn theo chiều x
	int y_val_; // lượng di chuyển viên đạn theo chiều y
	bool is_move_; // kiểm tra viên đạn có di chuyển không
	unsigned int buller_dir_; // hướng viên đạn
	unsigned int bullet_type_; // loại đạn
}; // lớp đạn kế thừa từ lớp BaseObject
#endif

// Explain
// Khi viên đạn bắn từ 0 cho đến vị trí nào đó trong màn hình trường hợp viên đạn vượt ra SCREEN_WIDTH thì phải biến mất 
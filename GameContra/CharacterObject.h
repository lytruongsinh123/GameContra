#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H
#include <vector>
#include "BaseFunction.h"
#include "BaseObject.h"
#include "BulletObject.h"
#define GRAVITY_SPEED 0.8 // tốc độ rơi
#define MAX_FALL_SPEED 10 // tốc độ rơi tối đa
#define PLAYER_SPEED  8// tốc độ di chuyển của nhân vật
#define PLAYER_JUMP_VAL 20 
class MainObject : public BaseObject {
public:
	MainObject();
	~MainObject();
	enum WalkType {
		WALK_RIGHT = 1,
		WALK_LEFT = 2,
		WALK_NONE = 0
	};
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
	void set_clips(); //xử lý animation

	void DoPlayer(Map& map_data); // xử lý va chạm với map
	void CheckToMap(Map& map_data); // kiểm tra va chạm với map
	void SetMapXY(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; }
	void CenterEntityOnMap(Map& map_data);
	void UpdateImagePlayer(SDL_Renderer* des);
	void set_bullet_list(std::vector<BulletObject*> bullet_list) { p_bullet_list_ = bullet_list; }
	std::vector<BulletObject*> get_bullet_list() const { return p_bullet_list_; } // lấy danh sách đạn
	void HandleBullet(SDL_Renderer* des);
	void IncreaseMoney(); // tăng tiền
private:
	int money_count_; // số tiền ăn được
	std::vector<BulletObject*> p_bullet_list_; // lưu danh sách đạn
	float x_val_; // khi ấn phải(trải) lùi(tiến) 1 lượng x_val_
	float y_val_;
	float x_pos_; // vị trí
	float y_pos_;
	int width_frame_; // lưu kích thước tấm ảnh
	int height_frame_;
	bool on_ground_; // kiểm tra nhân vật có đang ở trên mặt đất không

	SDL_Rect frame_clip_[8]; // Lưu các frame hay còn gọi là trạng thái nhân vật
	Input input_type_; // Lưu trạng thái nhân vật 
	int frame_; // Lưu chỉ số frame hiện tại
	int status_; // Lưu trạng thái nhân vật là left hay right phụ thuộc vào button sang trái sang phải lên xuống 
	int map_x_; // lưu vị trí nhân vật trên map
	int map_y_; // lưu vị trí nhân vật trên map


	int come_back_time_; // thời gian quay trở lại
};
#endif
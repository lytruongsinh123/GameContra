#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include "BaseFunction.h"
#include "BaseObject.h"

#define GRAVITY_SPEED 0.8 // tốc độ rơi
#define MAX_FALL_SPEED 10 // tốc độ rơi tối đa
#define PLAYER_SPEED  0.5// tốc độ di chuyển của nhân vật

class MainObject : public BaseObject {
public:
	MainObject();
	~MainObject();
	enum WalkType {
		WALK_RIGHT = 0,
		WALK_LEFT = 1,
	};
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
	void set_clips(); //xử lý animation

	void DoPlayer(Map& map_data); // xử lý va chạm với map
	void CheckToMap(Map& map_data); // kiểm tra va chạm với map

private:
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
};
#endif
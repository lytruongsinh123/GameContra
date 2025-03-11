#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H
#include "BaseFunction.h"
#include "BaseObject.h"
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
private:
	float x_val_; // khi ấn phải(trải) lùi(tiến) 1 lượng x_val_
	float y_val_; 
	float x_pos_; // vị trí
	float y_pos_;
	int width_frame_; // lưu kích thước tấm ảnh
	int height_frame_;

	SDL_Rect frame_clip_[8]; // Lưu các frame hay còn gọi là trạng thái nhân vật
	Input input_type_; // Lưu trạng thái nhân vật 
	int frame_; // Lưu chỉ số frame hiện tại
	int status_; // Lưu trạng thái nhân vật là left hay right phụ thuộc vào button sang trái sang phải lên xuống 
};
#endif
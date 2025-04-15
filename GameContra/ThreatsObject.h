
#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_

#include "BaseFunction.h"
#include "BaseObject.h"
#include "BulletObject.h"
#define THREAT_MAX_FALL_SPEED 10
#define THREAT_GRAVITY_SPEED 0.8
#define THREAT_FRAME_NUM 8
#define THREAT_SPEED 3
class ThreatsObject : public BaseObject // kế thừa từ object BaseObject
{
public:
    ThreatsObject();
    ~ThreatsObject();
	enum TypeMove // loại di chuyển của threat
	{
		STATIC_THREAT = 0,
		MOVE_IN_SPACE_THREAT = 1, 
		MOVE_ON_GROUND_THREAT = 2
	};
    void set_x_val(const float& xVal) { x_val_ = xVal; } // float tăng độ chính xác
    void set_y_val(const float& yVal) { y_val_ = yVal; }

    void set_x_pos(const float& xp) { x_pos_ = xp; }
    void set_y_pos(const float& yp) { y_pos_ = yp; }
    float get_x_pos() const { return x_pos_; } // lấy ra vị trí hiện tại của threats để làm gì đó
    float get_y_pos() const { return y_pos_; }
    void SetMapXY(const int& mp_x, const int& mp_y) { map_x_ = mp_x; map_y_ = mp_y; } // hàm để set map, định nghĩa giới hạn của bản đồ đối với threats

    void set_clips();
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des); // biểu diễn threat trên cửa sổ
    int get_width_frame() const { return width_frame_; }
    int get_height_frame() const { return height_frame_; }
    void DoPlayer(Map& gMap, SDL_Renderer* screen); // threats đứng yên hay di chuyển gì đó
    void CheckToMap(Map& gMap, SDL_Renderer* screen); // kéo threats theo khi mà bản đồ di chuyển
	void InitThreats(); // khởi tạo threat
	void set_type_move(const int& typemove) { type_move_ = typemove; }
	void setAnimationPos(const int& pos_a, const int& pos_b) { animation_a_ = pos_a; animation_b_ = pos_b; } // vị trí di chuyển
    void set_input_left(const int& ipleft) { input_type_.left_ = ipleft; }; // khi đến giới hạn a gán kiểu di chuyển = 0
	void ImpMoveType(SDL_Renderer* screen); // hàm xử lý di chuyển của threat
    SDL_Rect GetRectFrame();

	std::vector<BulletObject*> get_bullet_list() const { return bullet_list_; } // hàm quản lý lấy ra danh sách bullet
    void set_bullet_list(const std::vector<BulletObject*>& bl_list) { bullet_list_ = bl_list; } // xử lý va chạm với đạn bắn ra

    void InitBullet(BulletObject* p_bullet, SDL_Renderer* screen); // xử lý thông số của đạn
    void MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit);
    void RemoveBullet(const int& idx);
private:

    int map_x_; // giới hạn với bản đồ
    int map_y_;
    float x_val_; // lưu trữ vận tốc của vật thể theo phương x
    float y_val_;
    float x_pos_; // vị trí của threat
    float y_pos_;
    bool on_ground_; // xem thử threat có đang ở mặt đất ko
    int come_back_time_; // thời gian quay trở lại khi rơi xuống vực thẳm
    SDL_Rect frame_clip_[THREAT_FRAME_NUM];
    int frame_; // quản lý các chỉ số frame
    int width_frame_; // quản lý chiều dài frame
    int height_frame_; // quản lý chiều cao frame


	int type_move_; // quản lý hình thức di chuyển của threat
    // di chuyển trong phạm vi a b
	int animation_a_; 
	int animation_b_; 
	Input input_type_; // quản lý hình thức di chuyển của threat

    std::vector<BulletObject*> bullet_list_;
};

#endif

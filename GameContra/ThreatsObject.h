
#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_

#include "BaseFunction.h"
#include "BaseObject.h"

#define THREAT_MAX_FALL_SPEED 10
#define THREAT_GRAVITY_SPEED 0.8
#define THREAT_FRAME_NUM 8

class ThreatsObject : public BaseObject // kế thừa từ object BaseObject
{
public:
    ThreatsObject();
    ~ThreatsObject();

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
    void DoPlayer(Map& gMap); // threats đứng yên hay di chuyển gì đó
    void CheckToMap(Map& gMap); // kéo threats theo khi mà bản đồ di chuyển
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

};

#endif
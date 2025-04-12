#ifndef PLAY_POWER_H
#define PLAY_POWER_H
#include "BaseFunction.h"
#include "BaseObject.h"
class PlayerPower : public BaseObject {
public:
	PlayerPower();
	~PlayerPower();
	void SetNumber(int num) { number_ = num; } // set số mạng
	void AddPos(const int& pos); // thêm vị trí vào danh sách
	void Show(SDL_Renderer* des); // hiện số mạng
	void Init(SDL_Renderer* screen); // khởi tạo số mạng
	void InCrease(); // tăng số mạng
	void DeCrease(); // giảm số mạng
private:
	int number_; // số mạng
	std::vector<int> pos_list_; // lưu vị trí x của các mạng ví dụ mạng có 3 thì phải có 3 vị trí

};

class PlayerMoney : public BaseObject {
public:
	PlayerMoney();
	~PlayerMoney();
	void Init(SDL_Renderer* screen); // khởi tạo vị tri ban đầu cho icon đồng tiền
	void Show(SDL_Renderer* screen); // hiện icon đồng tiền
	void SetPos(const int& x, const int& y) { x_pos_ = x; y_pos_ = y; } // set vị trí cho icon đồng tiền
private:
	int x_pos_;
	int y_pos_;
};
#endif
	

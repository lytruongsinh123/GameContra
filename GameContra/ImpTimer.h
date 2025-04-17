#ifndef IMP_TIMER_H_
#define IMP_TIMER_H_

class ImpTimer {
public:
	ImpTimer();
	~ImpTimer();
	void start();
	void stop();
	void paused();
	void unpaused();
	int get_ticks();
	bool is_started();
	bool is_paused();
private:
	int start_tick_; // thời gian bắt đầu
	int paused_tick_; // thời gian tạm dừng
	bool is_paused_; // kiểm tra có đang tạm dừng hay không
	bool is_started_; // kiểm tra có đang chạy hay không 
};


#endif
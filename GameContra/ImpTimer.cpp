#include "stdafx.h"
#include "ImpTimer.h"
#include "BaseFunction.h"

ImpTimer::ImpTimer() {
	start_tick_ = 0;
	paused_tick_ = 0;
	is_paused_ = false;
	is_started_ = false;
}
ImpTimer::~ImpTimer() {

}

void ImpTimer::start() {
	is_started_ = true;
	is_paused_ = false;
	start_tick_ = SDL_GetTicks();
}
void ImpTimer::stop() {
	is_paused_ = false;
	is_started_ = false;
}

void ImpTimer::paused() {
	if (is_started_ == true && is_paused_ == false) {
		is_paused_ = true;
		paused_tick_ = SDL_GetTicks() - start_tick_;
	}
}
void ImpTimer::unpaused() {
	if (is_paused_ == true) {
		is_paused_ = false;
		start_tick_ = SDL_GetTicks() - paused_tick_;
		paused_tick_ = 0;
	}
}
int ImpTimer::get_ticks() {
	if (is_started_ == true) {
		if (is_paused_ == true) {
			return paused_tick_;
		}
		else {
			return SDL_GetTicks() - start_tick_;
		}
	}
	return 0;
}
bool ImpTimer::is_started() {
	return is_started_;
}
bool ImpTimer::is_paused() {
	return is_paused_;
}
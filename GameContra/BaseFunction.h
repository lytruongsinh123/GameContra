#ifndef BASE_FUNCTION_H_
#define BASE_FUNCTION_H_

#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "stdafx.h"

static SDL_Window* g_window = NULL; //build form window
static SDL_Renderer* g_screen = NULL; // build form renderer
static SDL_Event g_event; // event

// SCREEN
const int SCREEN_WIDTH = 1280; // Width of screen = 1280
const int SCREEN_HEIGHT = 640; // Height of screen = 640
// Dinh dang man hinh
const int SCREEN_BPP = 35; // Bit per pixel


// COLOR
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;


// Screen
const int FRAME_PER_SECOND = 32; // số frame mỗi giây
const int RENDER_DRAW_COLOR = 0XFF;

#define BLANK_TILE 0
#define TILE_SIZE  64// Định nghĩa mắt lưới

#define MAX_MAP_X  400
#define MAX_MAP_Y  10

#define STATE_MONEY 8 // Chỉ cố của ô tiền
#define TREE1 6
#define DRUG_HP 7
#define TREE3 41
#define TREE4 42
#define TREE5 43
#define NEW_TYPE_BULLET 19
typedef struct {
	int left_; // di chuyển sang trái 
	int right_; // ______________phải
	int up_;
	int down_;
	int jump_;
} Input;
typedef struct {
	int start_X_; // ví dụ vị trí ô thứ 10 * 64 = 640
	int start_Y_;
	int max_X_; // chỉ số ô theo chiều X = start_X_ / TILE_SIZE ( Lấy phần nguyên )
	int max_Y_; // chỉ số ô theo chiều Y = start_X_ / TILE_SIZE ( Lấy phần nguyên )
	int tile[MAX_MAP_Y][MAX_MAP_X];
	const char* file_name_;

} Map;

namespace SDLCommonFunc {
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2); // kiểm tra va chạm
}
#endif // !BASE_FUNCTION_H_


#include "SDL.h"
#include "stdafx.h"
#include "BaseFunction.h"
#include "BaseObject.h"
#include "Game_map.h"
#include "CharacterObject.h"
#include "ImpTimer.h"
BaseObject g_background;
bool InitData() { // Khoi tao SDL
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0)
		return false;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"); //Set ti le chat luong cua renderer

	g_window = SDL_CreateWindow("Game Contra", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); // Tao cua so

	if (g_window == NULL) {
		success = false;
	}
	else {
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED); // Gan renderer cho cua so
		if (g_screen == NULL)
			success = false;
		else {
			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags))
				success = false;
		}
	}
	return success;
}

bool LoadBackground() { // Load background
	bool ret = g_background.LoadImg("img//background.png", g_screen);  // Load background from file
	if (ret == false)
		return false;

	return true;
}

void close() { // Giai phong bo nho 
	g_background.Free();

	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[]) {

	ImpTimer fps_timer;
	if (InitData() == false)
		return -1;

	if (LoadBackground() == false)
		return -1;



	GameMap game_map_;
	game_map_.LoadMap("map_good//map01.dat");
	game_map_.LoadTiles(g_screen);


	MainObject p_player;
	p_player.LoadImg("img//player_right1.png", g_screen);
	p_player.set_clips();

	bool is_quit = false;
	while (!is_quit) { // Game loop
		fps_timer.start(); // lưu thời gian khi bắt đầu game
		while (SDL_PollEvent(&g_event) != 0) {
			if (g_event.type == SDL_QUIT) {
				is_quit = true;
			}

			p_player.HandleInputAction(g_event, g_screen);
		}

		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR); // Set mau cho renderer
		SDL_RenderClear(g_screen); // Xoa renderer

		g_background.Render(g_screen, NULL); // Hien thi background
		game_map_.DrawMap(g_screen);
		Map map_data = game_map_.getMap();


		p_player.SetMapXY(map_data.start_X_, map_data.start_Y_);
		p_player.DoPlayer(map_data);
		p_player.Show(g_screen);


		game_map_.SetMap(map_data); // cập nhật vị trí mới cho start_X_ và start_Y_
		game_map_.DrawMap(g_screen); // vẽ lại map


		SDL_RenderPresent(g_screen); // Cap nhat renderer

		int real_imp_time = fps_timer.get_ticks(); // lấy thời gian thực sự trôi qua
		int time_one_frame = 1000 / FRAME_PER_SECOND;  // Thời gian thực hiện 1 frame
		if (real_imp_time < time_one_frame) {
			int delay_time = time_one_frame - real_imp_time; // thời gian cần delay
			if(delay_time >= 0) SDL_Delay(delay_time);
		}// Nếu thời gian thực tế nhỏ hơn thời gian 1 frame 
	}

	close();
	return 0;
}

// Explain
// nếu real_imp_time mất 10ms mà trong khi đó time_one_frame mất 20 ms => thì nó rất nhanh
// cần tạo độ trễ tạo ra sự cân bằng cho tất cả chương trình 
// Nếu delaytime càng lơn => chương trình càng chậm dần 
// delaytime lơn khi FRAME_PER_SECOND càng nhỏ 
// vì FPS càng nhỏ => time_one_frame càng to => hiệu số time_one_frame - real_imp_time càng to => delay_time càng to
// => FPS càng nhỏ => chương trình chạy càng chậm
// để chương trình chạy nhanh => tăng FPS
// FPS = 25 => 1 FRAME NẤT 40ms
// trong khí đó real_time = 27;
// fps = 25 hoặc 30 hoặc 40 tăng đến khi nào time_one_frame - real_imp_time = nhau
// vậy FPS  = 37 thì real_tine >= time_one
// => NẾU MÀ TỪ 37 TRỞ LÊN => real_time luôn lơn hơn time_one => delay_time < 0 =? độ trẽ = 0;
// chương trính nó đạt tới chất lượng tối đa
// Để FPS vượt qua giới hạn 37 thì bắt buộc real_time phải nhỏ hơn nữa 
// ví dụ real_time = 10 => FPS = 1000/10 = 100 
// real_time càng nhỏ khi cấu hình máy tính càng tốt
// Khi máy tính có cấu hình càng cao => fps càng to => chương trính chạy càng nhanh

// Đây là tỷ số FPS trong game
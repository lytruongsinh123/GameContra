#include "SDL.h"
#include "stdafx.h"
#include "BaseFunction.h"
#include "BaseObject.h"
#include "Game_map.h"
#include "CharacterObject.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
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

std::vector<ThreatsObject*> MakeThreadList() // hàm tạo đối tượng trên bản đồ
{
	std::vector<ThreatsObject*> list_threats; // vector chứa các đối tượng trên bản đồ
	ThreatsObject* dynamic_threats = new ThreatsObject[20]; // có 20 threats trên bản đồ
	for (int i = 0; i < 20; ++i) {
	
			ThreatsObject* p_threat = dynamic_threats + i;
			if (p_threat != NULL) {
				p_threat->LoadImg("img//threat_left1.png", g_screen); // Load hình ảnh threat

				p_threat->set_clips(); // tạo hiệu ứng di chuyển
				p_threat->InitThreats();
				p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT); // loại di chuyển của threat
				p_threat->set_x_pos(500 + i * 500); // cách phân bố đều trên 25000 pixels: ông này dùng vòng lặp để cho hiện threat sau mỗi 1200 pixels, vị trí đầu ở điểm pixel thứ 700 (phân bố đều)
				p_threat->set_y_pos(0); // phân bố ở ngay trên map'
				int pos1 = p_threat->get_x_pos() - 60;
				int pos2 = p_threat->get_x_pos() + 60;
				p_threat->setAnimationPos(pos1, pos2); // giới hạn di chuyển của threat
				p_threat->set_input_left(1); // di chuyển qua trái
				list_threats.push_back(p_threat);
			}
		}
	ThreatsObject* threats_objs = new ThreatsObject[20]; // có 20 threats trên bản đồ

	for (int i = 0; i < 20; ++i)
	{
		ThreatsObject* p_threat = threats_objs + i;
		if (p_threat != NULL) // chừng nào pointer chưa chỉ đến cuối dãy thì load image từng threat lên
		{
			p_threat->LoadImg("img//threat.png", g_screen); // load hình ảnh threat
			p_threat->set_clips();
			p_threat->set_x_pos(700 + i * 1200); // cách phân bố đều trên 25000 pixels: ông này dùng vòng lặp để cho hiện threat sau mỗi 1200 pixels, vị trí đầu ở điểm pixel thứ 700 (phân bố đều)
			p_threat->set_y_pos(250); // phân bố ở ngay trên map
			p_threat->set_type_move(ThreatsObject::STATIC_THREAT); // loại di chuyển của threat
			p_threat->set_input_left(0); // không di chuyển

			BulletObject* p_bullet = new BulletObject(); // tạo viên đạn
			p_threat->InitBullet(p_bullet, g_screen); // khởi tạo đạn lên screen
			list_threats.push_back(p_threat); // thêm vào danh sách
		}
	}
	return list_threats;
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


	std::vector<ThreatsObject*> threats_list = MakeThreadList(); // tạo 1 threats list

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

		p_player.HandleBullet(g_screen);
		p_player.SetMapXY(map_data.start_X_, map_data.start_Y_);
		p_player.DoPlayer(map_data);
		p_player.Show(g_screen);


		game_map_.SetMap(map_data); // cập nhật vị trí mới cho start_X_ và start_Y_
		game_map_.DrawMap(g_screen); // vẽ lại map

		for (int i = 0; i < threats_list.size(); i++)
		{
			ThreatsObject* p_threat = threats_list.at(i); // tức là lấy con trỏ ở vị trí i, nếu ko có thì trả về null
			if (p_threat != NULL)
			{
				p_threat->SetMapXY(map_data.start_X_, map_data.start_Y_); // đặt các threats vào các vị trí trên map theo tọa độ
				p_threat->ImpMoveType(g_screen); // xử lý di chuyển của threat

				p_threat->DoPlayer(map_data);
				p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threat->Show(g_screen); // show ra
			}

		}


		// Lấy danh sách các viên đạn của nhân vật game
		//std::vector<BulletObject*> bullet_list = p_player.get_bullet_list();
		//for (int bl = 0; bl < bullet_list.size(); bl++) {
		//	BulletObject* p_bullet = bullet_list.at(bl);
		//	if (p_bullet != NULL) {
		//		for (int t = 0; t < threats_list.size(); t++) {
		//			ThreatsObject* obj_threat = threats_list.at(t);
		//			if (obj_threat != NULL) {
		//				SDL_Rect tRect;
		//				tRect.x = obj_threat->GetRect().x;
		//				tRect.y = obj_threat->GetRect().y;
		//				tRect.w = obj_threat->get_width_frame();
		//				tRect.h = obj_threat->get_height_frame();

		//				SDL_Rect bRect = p_bullet->GetRect();

		//				bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);
		//				if (bCol) {
		//					p_player.RemoveBullet(bl); // xóa viên đạn
		//					obj_threat->Free(); // xóa threat
		//					threats_list.erase(threats_list.begin() + t); // xóa threat khỏi danh sách
		//				}
		//			}
		//		}
		//	}
		//}
		std::vector<BulletObject*> bullet_list = p_player.get_bullet_list();
		for (auto it_bullet = bullet_list.begin(); it_bullet != bullet_list.end(); ) {
			BulletObject* p_bullet = *it_bullet;
			if (p_bullet != NULL) {
				bool bullet_erased = false;
				for (auto it_threat = threats_list.begin(); it_threat != threats_list.end(); ) {
					ThreatsObject* obj_threat = *it_threat;
					if (obj_threat != NULL) {
						SDL_Rect tRect;
						tRect.x = obj_threat->GetRect().x;
						tRect.y = obj_threat->GetRect().y;
						tRect.w = obj_threat->get_width_frame();
						tRect.h = obj_threat->get_height_frame();

						SDL_Rect bRect = p_bullet->GetRect();

						bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);
						if (bCol) {
							p_player.RemoveBullet(std::distance(bullet_list.begin(), it_bullet)); // xóa viên đạn
							it_bullet = bullet_list.erase(it_bullet); // xóa viên đạn khỏi danh sách

							// Xóa tất cả các viên đạn của quái
							std::vector<BulletObject*> threat_bullets = obj_threat->get_bullet_list();
							for (auto it_threat_bullet = threat_bullets.begin(); it_threat_bullet != threat_bullets.end(); ++it_threat_bullet) {
								BulletObject* p_threat_bullet = *it_threat_bullet;
								if (p_threat_bullet != NULL) {
									delete p_threat_bullet;
									p_threat_bullet = NULL;
								}
							}
							obj_threat->set_bullet_list(std::vector<BulletObject*>()); // Làm rỗng danh sách đạn của quái

							obj_threat->Free(); // xóa threat
							it_threat = threats_list.erase(it_threat); // xóa threat khỏi danh sách
							bullet_erased = true;
							break; // thoát khỏi vòng lặp threat
						}
						else {
							++it_threat;
						}
					}
					else {
						++it_threat;
					}
				}
				if (!bullet_erased) {
					++it_bullet;
				}
			}
			else {
				++it_bullet;
			}
		}




		SDL_RenderPresent(g_screen); // Cap nhat renderer

		int real_imp_time = fps_timer.get_ticks(); // lấy thời gian thực sự trôi qua
		int time_one_frame = 1000 / FRAME_PER_SECOND;  // Thời gian thực hiện 1 frame
		if (real_imp_time < time_one_frame) {
			int delay_time = time_one_frame - real_imp_time; // thời gian cần delay
			if (delay_time >= 0) SDL_Delay(delay_time);
		}// Nếu thời gian thực tế nhỏ hơn thời gian 1 frame 
	}

	// giải phóng bộ nhớ
	for (int i = 0; i < threats_list.size(); i++)
	{
		ThreatsObject* p_threat = threats_list.at(i);
		if (p_threat != NULL)
		{
			p_threat->Free();
			p_threat = NULL;
		}
	}

	threats_list.clear();

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
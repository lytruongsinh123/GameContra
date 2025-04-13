#include "SDL.h"
#include "stdafx.h"
#include "BaseFunction.h"
#include "BaseObject.h"
#include "Game_map.h"
#include "CharacterObject.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "TextObject.h"
#include "PlayPower.h"
#include "Geometric.h"
#include "BossObject.h"


BaseObject g_background;
TTF_Font* font_time = NULL; // đối tượng font chữ hiện thời gian
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

		if (TTF_Init() == -1) { // Khoi tao font LỖI
			success = false;
		}
		font_time = TTF_OpenFont("font//dlxfont.ttf", 15); // mở font chữ
		if (font_time == NULL) {
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
				p_threat->set_y_pos(200); // phân bố ở ngay trên map'
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
			p_threat->LoadImg("img//threat_level2.png", g_screen); // load hình ảnh threat
			p_threat->set_clips();
			p_threat->set_x_pos(700 + i * 1500); // cách phân bố đều trên 25000 pixels: ông này dùng vòng lặp để cho hiện threat sau mỗi 1200 pixels, vị trí đầu ở điểm pixel thứ 700 (phân bố đều)
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



	PlayerPower player_power; // tạo đối tượng số mạng
	player_power.Init(g_screen); // khởi tạo số mạng
	PlayerMoney player_money; // tạo đối tượng đồng tiền
	player_money.Init(g_screen); // khởi tạo đồng tiền
	player_money.SetPos(SCREEN_WIDTH * 0.5 - 290, 8);



	std::vector<ThreatsObject*> threats_list = MakeThreadList(); // tạo 1 threats list

	//Boss Threat
	BossObject bossObject;
	bool ret = bossObject.LoadImg("img//boss_object.png", g_screen);
	bossObject.set_clips();
	int xPosBoss = MAX_MAP_X * TILE_SIZE - SCREEN_WIDTH * 0.6;
	bossObject.set_xpos(xPosBoss);
	bossObject.set_ypos(10);

	ExplosionObject exp_threat;
	ExplosionObject exp_main;

	bool tRet = exp_threat.LoadImg("img//exp3.png", g_screen); // load hình ảnh explosion
	if (!tRet) return -1;
	exp_threat.set_clip(); // set clip cho explosion
	tRet = exp_main.LoadImg("img//exp3.png", g_screen);
	exp_main.set_clip();
	if (!tRet) return 0;

	//--------------------------Hiện màn hình các số liên quan đến game--------------------------
	int num_die = 0; // mạng
	TextObject time_game;
	TextObject score_game;
	TextObject money_count;
	//--------------------------Hiện màn hình các số liên quan đến game--------------------------
	time_game.SetColor(TextObject::WHITE_TEXT); // set màu trắng cho chữ
	score_game.SetColor(TextObject::WHITE_TEXT); // set màu trắng cho chữ
	UINT score_val = 0;
	money_count.SetColor(TextObject::WHITE_TEXT); // set màu trắng cho chữ
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


		// Draw Geometric
		GeometricFormat rectangle_size(0, 0, SCREEN_WIDTH, 42);
		ColorData color_data(36, 36, 36);
		Geometric::RenderRectangle(rectangle_size, color_data, g_screen);
		GeometricFormat outline_size(1, 1, SCREEN_WIDTH - 1, 41);
		ColorData color_data2(255, 250, 250);
		Geometric::RenderOutline(outline_size, color_data2, g_screen);


		player_power.Show(g_screen); // hiện số mạng
		player_money.Show(g_screen); // hiện đồng tiền



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


			    
				SDL_Rect rect_player = p_player.GetRectFrame(); // lấy vị trí của nhân vật
				bool bCol1 = false;
				// kiểm tra va chạm giữa viên đạn và nhân vật
				std::vector<BulletObject*> tBullet_list = p_threat->get_bullet_list(); // lấy danh sách đạn của threat
				for (int jj = 0; jj < tBullet_list.size(); jj++) {
					BulletObject* pt_bullet = tBullet_list.at(jj); // lấy ra viên đạn
					if (pt_bullet != NULL) {
						// kiểm tra va chạm giữa viên đạn và nhân vật
						bCol1 = SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), rect_player); // kiểm tra va chạm giữa viên đạn và nhân vật
						if(bCol1) {
							cout << "co su va cham dan va nhan vat" << endl;
							p_threat->RemoveBullet(jj); // xóa viên đạn
							break; // khi xảy ra va chạm rồi sẽ thoát khỏi vòng lặp ko kiểm tra với các viên đạn còn lại
						}
					}
				}

				// kiểm tra va chạm giữa nhân vật và threat
				SDL_Rect rect_threat = p_threat->GetRectFrame(); // lấy vị trí của threat
				bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat); // kiểm tra va chạm giữa nhân vật và threat
				// khi chết hiện thông báo game over
				if (bCol2) {
					cout << "co su va cham nhan vat va threat" << endl;
				}

				if (bCol1 || bCol2) {
					int width_exp_frame = exp_main.get_frame_width(); // lấy frame của explosion
					int height_exp_frame = exp_main.get_frame_height(); // lấy chiều cao của frame explosion
					for (int ex = 0; ex < 4; ex++) {
						int x_pos = (p_player.GetRect().x + p_player.get_frame_width() * 0.5) - width_exp_frame * 0.5; // lấy vị trí để đặt tấm ảnh vụ nổ
						int y_pos = (p_player.GetRect().y + p_player.get_frame_height() * 0.5) - height_exp_frame * 0.5; // lấy vị trí để đặt tấm ảnh vụ nổ
						exp_main.set_frame(ex);
						exp_main.SetRect(x_pos, y_pos); // lấy tâm vị trí nổ là vị trí của nhân vật
						exp_main.Show(g_screen); // hiện ảnh vụ nổ
						SDL_RenderPresent(g_screen); // cập nhật renderer
					}
					num_die++;
					if (num_die <= 3) // mạng là 3
					{// hồi sinh
						p_player.SetRect(100, 0);
						p_player.set_comeback_time(60); // thời gian hồi sinh
						SDL_Delay(1000); // tạm dừng 1 giây
						player_power.DeCrease(); // giảm số mạng
						player_power.Render(g_screen); // hiện số mạng
						continue;
					}
					else {
						if (MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK) {
							p_threat->Free();
							close();
							SDL_Quit();
							return 0;
						}
					}
				}
			}
		}
		
		int frame_exp_width = exp_threat.get_frame_width(); // lấy frame của explosion
		int frame_exp_height = exp_threat.get_frame_height(); 

		// Lấy danh sách các viên đạn của nhân vật game
		/*
		std::vector<BulletObject*> bullet_list = p_player.get_bullet_list();
		for (int bl = 0; bl < bullet_list.size(); bl++) {
			BulletObject* p_bullet = bullet_list.at(bl);
			if (p_bullet != NULL) {
				for (int t = 0; t < threats_list.size(); t++) {
					ThreatsObject* obj_threat = threats_list.at(t);
					if (obj_threat != NULL) {
						SDL_Rect tRect;
						tRect.x = obj_threat->GetRect().x;
						tRect.y = obj_threat->GetRect().y;
						tRect.w = obj_threat->get_width_frame();
						tRect.h = obj_threat->get_height_frame();

						SDL_Rect bRect = p_bullet->GetRect();

						bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);
						if (bCol) {
							p_player.RemoveBullet(bl); // xóa viên đạn
							obj_threat->Free(); // xóa threat
							threats_list.erase(threats_list.begin() + t); // xóa threat khỏi danh sách
						}
					}
				}
			}
		}
		*/
		
		
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
							score_val++; // tăng điểm số khi bắn trúng quái
							for (int ex = 0; ex < NUM_FRAME_EXP; ex++) { // for chạy 8 khung hình của vụ nổ
								int x_pos = p_bullet->GetRect().x - frame_exp_width * 0.5; // lấy vị trí để đặt tấm ảnh vụ nổ // chính là vị trí viên đạn
								int y_pos = p_bullet->GetRect().y - frame_exp_height * 0.5;
								// lấy tâm vị trí nổ là vị trí của viên đạn tại vị trí viên đạn chạm quái, ảnh vụ nổ luôn nằm ở bên dưới 
								// ví dụ
								//  * (đây là viên đạn)
								//  ----------- //
								//  |         | //
								//  |         | //
								//  ----------- // đây là bức ảnh ở bên dưới vụ nổ

								exp_threat.set_frame(ex);
								exp_threat.SetRect(x_pos, y_pos);
								exp_threat.Show(g_screen);
							} 

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




		// Show game time
		std::string str_time = "Time: ";
		Uint32 time_val = SDL_GetTicks() / 1000; // lấy thời gian thực tế
		Uint32 time_game_val =  300 - time_val; // lấy thời gian đếm ngược từ 300 trở lại
		if (time_game_val <= 0) { // hết giờ chưa về đích
			if (MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK) {
				is_quit = true;
				break;
			}
		}
		else {
			std::string str_val = std::to_string(time_game_val); // chuyển đổi số thành string
			str_time += str_val; // nối chuỗi Time: và thời gian

			time_game.SetText(str_time); // set nội dung cho chữ
			time_game.LoadFromRenderText(font_time, g_screen);
			time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 15);
		}
		// Show score
		std::string str_score = "Score: ";
		std::string str_val = std::to_string(score_val); // chuyển đổi số thành string
		str_score += str_val; // nối chuỗi Score: và điểm số
		score_game.SetText(str_score); // set nội dung cho chữ
		score_game.LoadFromRenderText(font_time, g_screen);
		score_game.RenderText(g_screen, SCREEN_WIDTH*0.5 - 50, 15);

		// Show money count
		std::string str_money_val = std::to_string(p_player.GetMoneyCount()); // chuyển đổi số thành string
		money_count.SetText(str_money_val); // set nội dung cho chữ
		money_count.LoadFromRenderText(font_time, g_screen);
		money_count.RenderText(g_screen, SCREEN_WIDTH * 0.5 - 250, 15);

		//Show Boss
		int val = MAX_MAP_X * TILE_SIZE - (map_data.start_X_ + p_player.GetRect().x);
		if (val <= SCREEN_WIDTH) {
			bossObject.SetMapXY(map_data.start_X_, map_data.start_Y_);
			bossObject.DoPlayer(map_data);
			bossObject.MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
			bossObject.Show(g_screen);
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
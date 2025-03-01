#include "stdafx.h"
#include "Game_map.h"

void GameMap::LoadMap(char* name) {
	FILE* fp = NULL;
	fopen_s(&fp, name, "rb");
	if (fp == NULL) {
		return;
	}
	game_map_.max_X_ = 0;
	game_map_.max_Y_ = 0;
	for (int i = 0; i < MAX_MAP_Y; i++) {
		for (int j = 0; j < MAX_MAP_X; j++) {
			fscanf_s(fp, "%d", &game_map_.tile[i][j]); // đọc chỉ số từ file map ghi vào game_map
			int val = game_map_.tile[i][j];
			if (val > 0) {
				if (j > game_map_.max_X_) {
					game_map_.max_X_ = j;
				}
				if (i > game_map_.max_Y_) {
					game_map_.max_Y_ = i;
				}
			}
		}
	}
	game_map_.max_X_ = (game_map_.max_X_ + 1)* TILE_SIZE;
	game_map_.max_Y_ = (game_map_.max_Y_ + 1)* TILE_SIZE;
	game_map_.start_X_ = 0;
	game_map_.start_Y_ = 0;
	game_map_.file_name_ = name;
	fclose(fp);
}
// load image
void GameMap::LoadTiles(SDL_Renderer* screen) {
	char file_img[10];
	FILE* fp = NULL;
	for (int i = 0; i < MAX_TILES; i++) {
		sprintf_s(file_img, "map/%d.png", i); // ví dụ chuyển file map/1.png vào mảng file_img

		fopen_s(&fp, file_img, "rb");
		// Nếu fp == NULL thì tấm ảnh ko load được 
		if (fp == NULL) {
			continue;
		}

		// nếu đọc được ảnh 
		fclose(fp);
		tile_mat[i].LoadImg(file_img, screen); // load lên màn hình ví dụ gán tile_mat[1] = ảnh màu xanh
	}
}

// vẽ map fill hình ảnh vào ô
void GameMap::DrawMap(SDL_Renderer* screen) {
	int x1 = 0;
	int x2 = 0;
	int y1 = 0; 
	int y2 = 0;
	int map_x = 0;
	int map_y = 0;

	map_x = game_map_.start_X_ / TILE_SIZE;
	x1 = (game_map_.start_X_ % TILE_SIZE) * -1;
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

	map_y = game_map_.start_Y_ / TILE_SIZE;
	y1 = (game_map_.start_Y_ % TILE_SIZE) * -1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);
	for (int i = y1; i < y2; i += TILE_SIZE) {
		map_x = game_map_.start_X_ / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE) {
			int val = game_map_.tile[map_y][map_x];
			if (val > 0) {
				tile_mat[val].SetRect(i, j);
				tile_mat[val].Render(screen);
			}
			map_x++;
		}
		map_y++;
	}
}
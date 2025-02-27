
#include "stdafx.h"
#include "BaseFunction.h"
#include "BaseObject.h"
#include "SDL.h"

BaseObject g_backgorund;

bool InitData() { // Khoi tao SDL
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0)
		return false;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"); //Set ti le chat luong cua renderer

	g_window = SDL_CreateWindow("Game Contra", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); // Tao cua so

	if(g_window == NULL) {
		success = false;
	} else {
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED); // Gan renderer cho cua so
			if(g_screen == NULL) 
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
	if (InitData() == false)
		return -1;

	if (LoadBackground() == false)
		return -1;

	bool is_quit = false;
	while (!is_quit) { // Game loop
		while(SDL_PollEvent(&g_event) != 0) {
			if(g_event.type == SDL_QUIT) {
				is_quit = true;
			}
		}

		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR); // Set mau cho renderer
		SDL_RenderClear(g_screen); // Xoa renderer

		g_background.Render(g_screen, NULL); // Hien thi background

		SDL_RenderPresent(g_screen); // Cap nhat renderer
	}

	close();
	return 0;
}
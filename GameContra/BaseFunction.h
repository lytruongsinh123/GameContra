#ifndef BASE_FUNCTION_H_
#define BASE_FUNCTION_H_

#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

static SDL_Window* g_window = NULL; //build form window
static SDL_Renderer* g_screen = NULL; // build form renderer
static SDL_Event g_event; // event

// SCREEN
const int SCREEN_WIDTH = 1280; // Width of screen = 1280
const int SCREEN_HEIGHT = 640; // Height of screen = 640
// Dinh dang man hinh
const int SCREEN_BPP = 32; // Bit per pixel


// COLOR
const int COLOR_KEY_R = 167; 
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0XFF;
#endif // !BASE_FUNCTION_H_


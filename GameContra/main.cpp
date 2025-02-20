#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;
Mix_Music* music = nullptr;
SDL_Texture* imageTexture = nullptr;

// Hàm tải ảnh
SDL_Texture* LoadTexture(const char* file) {
    SDL_Surface* surface = IMG_Load(file);
    if (!surface) {
        std::cout << "Lỗi tải ảnh: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

// Hàm hiển thị chữ
SDL_Texture* RenderText(const char* text, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        std::cout << "Lỗi render text: " << TTF_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

// Khởi tạo SDL2 và các thư viện
bool InitSDL() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cout << "Lỗi khởi tạo SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "Lỗi SDL_image: " << IMG_GetError() << std::endl;
        return false;
    }
    if (TTF_Init() == -1) {
        std::cout << "Lỗi SDL_ttf: " << TTF_GetError() << std::endl;
        return false;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "Lỗi SDL_mixer: " << Mix_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Test SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!window || !renderer) {
        std::cout << "Lỗi tạo cửa sổ hoặc renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

// Load tài nguyên
bool LoadMedia() {
    font = TTF_OpenFont("arial.ttf", 28);
    if (!font) {
        std::cout << "Lỗi tải font: " << TTF_GetError() << std::endl;
        return false;
    }

    imageTexture = LoadTexture("image.png");
    if (!imageTexture) return false;

    music = Mix_LoadMUS("music.mp3");
    if (!music) {
        std::cout << "Lỗi tải nhạc: " << Mix_GetError() << std::endl;
        return false;
    }

    return true;
}

// Vẽ màn hình
void Render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect imgRect = { 150, 100, 500, 300 };
    SDL_RenderCopy(renderer, imageTexture, nullptr, &imgRect);

    SDL_Color white = { 255, 255, 255 };
    SDL_Texture* textTexture = RenderText("SDL2 Test: Image, Text, Sound", white);
    SDL_Rect textRect = { 200, 450, 400, 50 };
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
    SDL_DestroyTexture(textTexture);

    SDL_RenderPresent(renderer);
}

// Giải phóng bộ nhớ
void Cleanup() {
    SDL_DestroyTexture(imageTexture);
    Mix_FreeMusic(music);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    if (!InitSDL()) return 1;
    if (!LoadMedia()) return 1;

    Mix_PlayMusic(music, -1);

    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }
        Render();
        SDL_Delay(16);
    }

    Cleanup();
    return 0;
}

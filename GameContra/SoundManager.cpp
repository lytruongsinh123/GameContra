#include "SoundManager.h"

// Hàm khởi tạo, đặt biến mInitialized ban đầu là false.
SoundManager::SoundManager() : mInitialized(false) {}

// Hàm hủy của lớp, đảm bảo đóng SDL_mixer khi đối tượng bị hủy.
SoundManager::~SoundManager() {
    close();
}

// Khởi tạo SDL_mixer với các thông số cho phép bạn cấu hình tần số, định dạng, số kênh và kích thước buffer.
bool SoundManager::init(int frequency, Uint16 format, int channels, int chunksize) {
    if (Mix_OpenAudio(frequency, format, channels, chunksize) < 0) {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        mInitialized = false;
    }
    else {
        mInitialized = true;
    }
    return mInitialized;
}

// Tải nhạc nền (Mix_Music) từ đường dẫn file
Mix_Music* SoundManager::loadMusic(const std::string& filePath) {
    if (!mInitialized) return nullptr;
    Mix_Music* music = Mix_LoadMUS(filePath.c_str());
    if (music == nullptr) {
        std::cout << "Failed to load music (" << filePath << ")! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    return music;
}

// Tải hiệu ứng âm thanh (Mix_Chunk) từ đường dẫn file
Mix_Chunk* SoundManager::loadEffect(const std::string& filePath) {
    if (!mInitialized) return nullptr;
    Mix_Chunk* effect = Mix_LoadWAV(filePath.c_str());
    if (effect == nullptr) {
        std::cout << "Failed to load effect (" << filePath << ")! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    return effect;
}

// Phát nhạc nền với số lần lặp lại quy định (default -1: chạy vô tận)
bool SoundManager::playMusic(Mix_Music* music, int loops) {
    if (!mInitialized || music == nullptr) return false;
    if (Mix_PlayMusic(music, loops) == -1) {
        std::cout << "Failed to play music! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

// Phát hiệu ứng âm thanh; Mix_PlayChannel với kênh -1 để tự động chọn kênh trống
bool SoundManager::playEffect(Mix_Chunk* effect, int loops) {
    if (!mInitialized || effect == nullptr) return false;
    int channel = Mix_PlayChannel(-1, effect, loops);
    if (channel == -1) {
        std::cout << "Failed to play effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}


// Giải phóng nhạc nền đã tải
void SoundManager::freeMusic(Mix_Music* music) {
    if (music != nullptr) {
        Mix_FreeMusic(music);
        music = nullptr;
    }
}

// Giải phóng hiệu ứng âm thanh đã tải
void SoundManager::freeEffect(Mix_Chunk* effect) {
    if (effect != nullptr) {
        Mix_FreeChunk(effect);
		effect = nullptr;
    }
}

// Đóng SDL_mixer và đặt lại trạng thái khởi tạo
void SoundManager::close() {
    if (mInitialized) {
        Mix_CloseAudio();
        mInitialized = false;
    }
}

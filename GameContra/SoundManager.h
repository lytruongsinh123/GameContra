#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "SDL.h"
#include "SDL_mixer.h"
#include <string>
#include <iostream>

// Lớp SoundManager quản lý âm thanh sử dụng SDL_mixer
class SoundManager {
public:
    SoundManager();
    ~SoundManager();

    // Khởi tạo SDL_mixer với thông số mặc định (có thể cấu hình lại nếu cần)
    bool init(int frequency = 44100, Uint16 format = MIX_DEFAULT_FORMAT, int channels = 2, int chunksize = 2048);

    // Tải file nhạc nền (Mix_Music) từ đường dẫn file
    Mix_Music* loadMusic(const std::string& filePath);

    // Tải file hiệu ứng âm thanh (Mix_Chunk) từ đường dẫn file
    Mix_Chunk* loadEffect(const std::string& filePath);

    // Phát nhạc nền; loops = -1 để chạy vô tận
    bool playMusic(Mix_Music* music, int loops = -1);

    // Phát hiệu ứng âm thanh; loops = 0 để phát 1 lần
    bool playEffect(Mix_Chunk* effect, int loops = 0);

    bool loadCoinSound(const std::string& filePath);
    void playCoinSound();

    // Giải phóng nhạc nền
    void freeMusic(Mix_Music* music);

    // Giải phóng hiệu ứng âm thanh
    void freeEffect(Mix_Chunk* effect);

    // Đóng SDL_mixer và giải phóng tài nguyên liên quan
    void close();

private:
    bool mInitialized; // Kiểm tra SDL_mixer đã được khởi tạo hay chưa
    Mix_Chunk* m_coinSound = nullptr;
};

#endif // SOUNDMANAGER_H

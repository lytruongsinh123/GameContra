#ifndef RANKING_MANAGER_H_
#define RANKING_MANAGER_H_

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "TextObject.h"

struct PlayerScore {
    std::string name;
    int score;
};

class RankingManager {
public:
    RankingManager(const std::string& file_path);
    void LoadRanking();
    void SaveRanking();

    void AddScore(const PlayerScore& ps);
    void RenderRanking(SDL_Renderer* screen, TTF_Font* font);

private:
    std::string file_path_;
    std::vector<PlayerScore> ranking_;
};

#endif

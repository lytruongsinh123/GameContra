#ifndef GAME_MENU_H_
#define GAME_MENU_H_

#include "BaseObject.h"
#include "TextObject.h"
#include "BaseFunction.h"

class Menu {
public:
    Menu();
    ~Menu();

    bool Init(SDL_Renderer* renderer);
    int ShowMenu(SDL_Renderer* renderer, TTF_Font* font);

private:
    BaseObject background_;
    TextObject start_text_;
    TextObject exit_text_;
    TextObject start_rect_;
    TextObject exit_rect_;
};

#endif // GAME_MENU_H_

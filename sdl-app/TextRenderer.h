#pragma once
// TODO I would really like to forward delcare this, but ran into trouble
// because TTF_Font is defined as 
// typedef struct _TTF_Font TTF_Font;
#include <SDL_ttf.h>

#include <string>

class Game;
class SDL_Rect;

class TextRenderer {
public:
    TextRenderer(Game* game);
    ~TextRenderer();

    void Render(const std::string& message, const SDL_Rect& rect);

private:
    Game* m_game;
    TTF_Font* m_font;
};

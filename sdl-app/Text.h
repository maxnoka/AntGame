#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include <memory>

class Text {
public:
    Text(const std::string& message, const SDL_Color& color);

    void Render(SDL_Renderer* renderer, const SDL_Rect& rect);

private:
    std::string m_message;
    SDL_Color m_color;

    std::shared_ptr<TTF_Font> m_font;
    std::shared_ptr<SDL_Surface> m_surface;

    static void FontDeleter(TTF_Font* f);
    static void SurfaceDeleter(SDL_Surface* s);
};

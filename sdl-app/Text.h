#include <string>

#include <SDL.h>

class Text {
public:
    Text(const std::string& message, const SDL_Color& color)
    : m_message(message)
    , m_color(color)
    {}

    void Render();

private:
    std::string m_message;
    SDL_Color m_color;
};

#include "TextRenderer.h"
#include "Game.h"

#include <SDL.h>
#include <easyloggingpp/easylogging++.h>
#include <scopeguard/scopeguard.hpp>


#define _GETASSETPATH(asset) ASSET_PATH asset
#define GETASSETPATH(asset) _GETASSETPATH(asset)

namespace {
    constexpr auto kFontPath = GETASSETPATH("cour.ttf");
    constexpr SDL_Color red = {0xff, 0, 0};
}

TextRenderer::TextRenderer(Game* game)
    : m_game(game)
    , m_font()
{
    TTF_Init();

    m_font = TTF_OpenFont(kFontPath, 72);

    if (!m_font) {
        LOG(ERROR) << "Could not open font [ " << kFontPath << " ]";
    }

}

TextRenderer::~TextRenderer() {
    if (m_font) {
        TTF_CloseFont(m_font);
    }

    TTF_Quit();
}

void TextRenderer::Render(const std::string& message, const SDL_Rect& rect) {
    if (!m_font) {
        // logged when we initially failed to open the font
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Solid(m_font, message.data(), red);
    // now you can convert it into a texture
    if (!surface) {
        LOG(ERROR) << "No surface. Cannot render text";
        return;
    }
    auto destroySurface = sg::make_scope_guard(
        [surface](){
            if (surface) {
                SDL_FreeSurface(surface);
            }
        }
    );

    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_game->m_renderer, surface);
    if (!texture) {
        LOG(ERROR) << "could not create message";
        return;
    }
    auto destroyTexture = sg::make_scope_guard(
        [texture](){
            if (texture) {
                SDL_DestroyTexture(texture);
            }
        }
    );

    SDL_RenderCopy(m_game->m_renderer, texture, NULL, &rect);
}

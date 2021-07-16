#include "Text.h"

#include <easyloggingpp/easylogging++.h>
#include <scopeguard/scopeguard.hpp>

#define _GETASSETPATH(asset) ASSET_PATH asset
#define GETASSETPATH(asset) _GETASSETPATH(asset)

namespace {
    constexpr auto kFontPath = GETASSETPATH("cour.ttf");
}

Text::Text(const std::string& message, const SDL_Color& color)
    : m_message(message)
    , m_color(color)
    , m_font(TTF_OpenFont(kFontPath, 72), FontDeleter)
    , m_surface(nullptr, SurfaceDeleter)
    {
        if (!m_font) {
            LOG(ERROR) << "Could not open font [ " << kFontPath << " ]";
        }

        m_surface.reset(
            TTF_RenderText_Solid(m_font.get(), m_message.data(), m_color),
            SurfaceDeleter);
    }

void Text::Render(SDL_Renderer* renderer, const SDL_Rect& rect) {
    // now you can convert it into a texture
    if (!m_surface) {
        LOG(ERROR) << "No surface. Cannot render text";
        return;
    }

    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, m_surface.get());
    if (!message) {
        LOG(ERROR) << "could not create message";
        return;
    }
    auto destroyTexture = sg::make_scope_guard(
        [message](){
            if (message) {
                SDL_DestroyTexture(message);
            }
        }
    );

    SDL_RenderCopy(renderer, message, NULL, &rect);
}

void Text::FontDeleter(TTF_Font* f) {
    if (f) {
        TTF_CloseFont(f);
    }
}

void Text::SurfaceDeleter(SDL_Surface* s) {
    if (s) {
        SDL_FreeSurface(s);
    }
}

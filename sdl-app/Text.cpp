#include "Text.h"

#include <SDL_ttf.h>
#include <easyloggingpp/easylogging++.h>
#include <scopeguard/scopeguard.hpp>

void Text::Render(SDL_Renderer* renderer, const SDL_Rect& rect) {
    TTF_Font* Sans = TTF_OpenFont("../../assets/cour.ttf", 48);
    if (!Sans) {
        LOG(ERROR) << "no font lmao";
        return;
    }
    auto closeFont = sg::make_scope_guard(
        [Sans](){
            if (Sans) {
                TTF_CloseFont(Sans);
            }
        }
    );

    SDL_Surface* surfaceMessage =
        TTF_RenderText_Solid(Sans, m_message.data(), m_color); 
    if (!surfaceMessage) {
        LOG(ERROR) << "could not create surface";
        return;
    }
    auto freeSurface = sg::make_scope_guard(
        [surfaceMessage](){
            if (surfaceMessage) {
                SDL_FreeSurface(surfaceMessage);
            }
        }
    );

    // now you can convert it into a texture
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    if (!Message) {
        LOG(ERROR) << "could not create message";
        return;
    }
    auto destroyTexture = sg::make_scope_guard(
        [Message](){
            if (Message) {
                SDL_DestroyTexture(Message);
            }
        }
    );

    SDL_RenderCopy(renderer, Message, NULL, &rect);
}
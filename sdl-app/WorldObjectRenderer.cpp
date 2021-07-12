#include "WorldObjectRenderer.h"
#include "Camera.h"
#include "Game.h"

#include <antgame/Ant.h>
#include <antgame/Plant.h>

#include <SDL.h>
#include <SDL_ttf.h>

#include <easyloggingpp/easylogging++.h>


namespace {
    Box ExpandPointToRect(const Point& point, float size) {
        auto min_x = point.get<0>() - size / 2;
        auto min_y = point.get<1>() - size / 2;
        auto max_x = point.get<0>() + size / 2;
        auto max_y = point.get<1>() + size / 2;
        return Box({min_x, min_y}, {max_x, max_y});
    }

    SDL_FRect BoxToFRectTransform(const Box& box, const Camera& cam) {
        auto min = cam.WorldToScreenTransform(box.min_corner());
        auto max = cam.WorldToScreenTransform(box.max_corner());

        return SDL_FRect { min.x, min.y, (max.x - min.x), (max.y - min.y)};
    }
}

void WorldObjectRenderer::Visit(const Ant& visitee) const {
    static constexpr auto kAntSize = 0.5;

    SDL_SetRenderDrawColor(m_game->m_renderer, 0x94, 0x58, 0x0A, 0xFF);

    auto expanded = ExpandPointToRect(visitee.GetPosition(), kAntSize);
    auto rect = BoxToFRectTransform(expanded, m_game->m_camera);
    SDL_RenderFillRectF(m_game->m_renderer, &rect);
}

void WorldObjectRenderer::Visit(const Plant& visitee) const {
    static constexpr auto kFoodSize = 0.2;

    if(m_game->m_debugMode)
    {
        //this opens a font style and sets a size
        TTF_Font* Sans = TTF_OpenFont("../../assets/cour.ttf", 48);

        if (!Sans) {
            LOG(ERROR) << "no font lmao";
        }

        // this is the color in rgb format,
        // maxing out all would give you the color white,
        // and it will be your text's color
        SDL_Color White = {0xff, 0, 0};

        // as TTF_RenderText_Solid could only be used on
        // SDL_Surface then you have to create the surface first
        SDL_Surface* surfaceMessage =
            TTF_RenderText_Solid(Sans, visitee.Print(false).data(), White); 

        // now you can convert it into a texture
        SDL_Texture* Message = SDL_CreateTextureFromSurface(m_game->m_renderer, surfaceMessage);


        auto point = m_game->m_camera.WorldToScreenTransform(visitee.GetPosition());
        SDL_Rect Message_rect; //create a rect
        Message_rect.x = point.x;  //controls the rect's x coordinate 
        Message_rect.y = point.y; // controls the rect's y coordinte
        Message_rect.w = 200; // controls the width of the rect
        Message_rect.h = 50; // controls the height of the rect

        // (0,0) is on the top left of the window/screen,
        // think a rect as the text's box,
        // that way it would be very simple to understand

        // Now since it's a texture, you have to put RenderCopy
        // in your game loop area, the area where the whole code executes

        // you put the renderer's name first, the Message,
        // the crop size (you can ignore this if you don't want
        // to dabble with cropping), and the rect which is the size
        // and coordinate of your texture
        SDL_RenderCopy(m_game->m_renderer, Message, NULL, &Message_rect);

        // Don't forget to free your surface and texture
        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(Message);
        TTF_CloseFont(Sans);

    }

    
    SDL_SetRenderDrawColor(m_game->m_renderer, 0x00, 0xFF, 0x00, 0xFF);
        
    

    auto expanded = ExpandPointToRect(visitee.GetPosition(), kFoodSize);
    auto rect = BoxToFRectTransform(expanded, m_game->m_camera);
    SDL_RenderFillRectF(m_game->m_renderer, &rect);
} 

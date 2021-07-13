#include "WorldObjectRenderer.h"
#include "Camera.h"
#include "Game.h"
#include "Text.h"

#include <antgame/Ant.h>
#include <antgame/Plant.h>

#include <SDL.h>

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

    if(m_game->m_debugMode) {
        auto point = m_game->m_camera.WorldToScreenTransform(visitee.GetPosition());
        SDL_Rect Message_rect; //create a rect
        Message_rect.x = point.x;  //controls the rect's x coordinate 
        Message_rect.y = point.y; // controls the rect's y coordinte
        Message_rect.w = 200; // controls the width of the rect
        Message_rect.h = 50; // controls the height of the rect

        SDL_Color White = {0xff, 0, 0};

        Text debugText(visitee.Print(false).data(), White); 

        debugText.Render(m_game->m_renderer, Message_rect);
    }

    
    SDL_SetRenderDrawColor(m_game->m_renderer, 0x00, 0xFF, 0x00, 0xFF);
        
    

    auto expanded = ExpandPointToRect(visitee.GetPosition(), kFoodSize);
    auto rect = BoxToFRectTransform(expanded, m_game->m_camera);
    SDL_RenderFillRectF(m_game->m_renderer, &rect);
} 

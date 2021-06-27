#include "WorldObjectRenderer.h"
#include "Camera.h"

#include <antgame/Ant.h>
#include <antgame/Plant.h>

#include <SDL.h>

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

    SDL_SetRenderDrawColor(m_renderer, 0xFF, 0x00, 0x00, 0xFF);

    auto expanded = ExpandPointToRect(visitee.GetPosition(), kAntSize);
    auto rect = BoxToFRectTransform(expanded, *m_camera);
    SDL_RenderFillRectF(m_renderer, &rect);
}

void WorldObjectRenderer::Visit(const Plant& visitee) const {
    static constexpr auto kFoodSize = 0.2;

    SDL_SetRenderDrawColor(m_renderer, 0x00, 0xFF, 0x00, 0xFF);

    auto expanded = ExpandPointToRect(visitee.GetPosition(), kFoodSize);
    auto rect = BoxToFRectTransform(expanded, *m_camera);
    SDL_RenderFillRectF(m_renderer, &rect);
} 

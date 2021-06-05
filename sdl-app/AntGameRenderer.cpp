#include "AntGameRenderer.h"

#include <SDL.h>

#include <algorithm>

namespace {
    Box ExpandPointToRect(const WorldObject& point, float size) {
        auto min_x = point.GetPosX() - size / 2;
        auto min_y = point.GetPosY() - size / 2;
        auto max_x = point.GetPosX() + size / 2;
        auto max_y = point.GetPosY() + size / 2;
        return Box({min_x, min_y}, {max_x, max_y});
    }

    SDL_FRect BoxToFRectTransform(const Box& box, const Camera& cam) {
        auto min = cam.WorldToScreenTransform(box.min_corner());
        auto max = cam.WorldToScreenTransform(box.max_corner());

        return SDL_FRect { min.x, min.y, (max.x - min.x), (max.y - min.y)};
    }

    constexpr auto kDefaultSize = 0.5;
}

void Render(SDL_Renderer* renderer, World world, Camera camera) {
    auto frustrum = camera.GetFrustrum();

    auto [objectsIt, objectsItEnd] = world.GetObjects(frustrum);
    std::vector<SDL_FRect> pointsToRender(std::distance(objectsIt, objectsItEnd));
    auto it = std::inserter(pointsToRender, pointsToRender.begin());
    std::transform(
        objectsIt,
        objectsItEnd,
        it,
        [&camera](const std::shared_ptr<WorldObject>& wobj) {
            auto rect = ExpandPointToRect(*wobj, kDefaultSize);
            return BoxToFRectTransform(rect, camera);
        } 
    );

    SDL_RenderDrawRectsF(
        renderer,
        pointsToRender.data(),
        pointsToRender.size()
    );
}
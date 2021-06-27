#pragma once

#include <antgame/Visitor.h>

class Camera;
class SDL_Renderer;

class WorldObjectRenderer final : public Visitor {
public:
    WorldObjectRenderer(SDL_Renderer* renderer, const Camera& cam)
    : m_renderer(renderer)
    , m_camera(&cam)
    {}

    virtual void Visit(const Ant& visitee) const override final;
    virtual void Visit(const Plant& visitee) const override final;

private:
    SDL_Renderer* m_renderer;
    const Camera* m_camera;
};

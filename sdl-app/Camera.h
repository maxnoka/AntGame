#pragma once

#include <antgame/WorldObject.h>
#include <SDL.h>

class Camera {
public:

    Camera(const Point& initialPosition, float zoom, float rotation, unsigned int windowWidth, unsigned int windowHeight)
    : m_position(initialPosition) 
    , m_zoom(zoom)
    , m_rotation(rotation)
    , m_windowWidth(windowWidth)
    , m_windowHeight(windowHeight)
    {}
    
    SDL_FPoint WorldToScreenTransform(const Point& point) const;
    Point ScreenToWorldTransform(const SDL_FPoint& point) const;

    Box GetFrustrum() const;

private:
    Point m_position;
    float m_zoom;
    float m_rotation;
    unsigned int m_windowWidth;
    unsigned int m_windowHeight;
};
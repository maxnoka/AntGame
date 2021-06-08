#pragma once

#include <antgame/WorldObject.h>
#include <SDL.h>
#include <math.h>

class Camera {
public:

    Camera(const Point& initialPosition, int zoom, float rotation, unsigned int windowWidth, unsigned int windowHeight)
    : m_position(initialPosition) 
    , m_zoom(zoom)
    , m_rotation(rotation)
    , m_windowWidth(windowWidth)
    , m_windowHeight(windowHeight)
    , m_frustrum()
    {
        UpdateFrustrum();
    }
    
    SDL_FPoint WorldToScreenTransform(const Point& point) const;
    Point ScreenToWorldTransform(const SDL_FPoint& point) const;

    const Box& GetFrustrum() const { return m_frustrum; }

    int GetZoom() {
        return m_zoom;
    }

    void UpdateZoom(float changeinzoom) {
        m_zoom = m_zoom + changeinzoom;
    }

    void UpdatePosition(int x, int y);

private:
    Point m_position;
    float m_zoom;
    float m_rotation;
    unsigned int m_windowWidth;
    unsigned int m_windowHeight;

    void UpdateFrustrum();

    // Cached variables (remain valid while the above do not change)
    Box m_frustrum;
};

#pragma once
#include "MessagePassing.h"
#include "InputHandler.h"

#include <antgame/WorldObject.h>
#include <SDL.h>
#include <math.h>

class Camera final : public IMessageSubscriber<KeysDict> {
public:
    enum class Direction {
        Left = 0,
        Right,
        Up,
        Down
    };

    Camera(
        const Point& initialPosition, 
        int zoom, 
        float rotation,
        unsigned int windowWidth,
        unsigned int windowHeight);

    virtual void OnMessage(const KeysDict& keysDown) override;
    
    SDL_FPoint WorldToScreenTransform(const Point& point) const;
    Point ScreenToWorldTransform(const SDL_FPoint& point) const;

    const Box& GetFrustrum() const { return m_frustrum; }
    int GetZoom() { return m_zoom; }

    void ZoomIn();
    void ZoomOut();
    void Move(const Direction direc);

private:
    Point m_position;
    float m_zoom;
    float m_rotation;
    unsigned int m_windowWidth;
    unsigned int m_windowHeight;

    void UpdateZoom(float changeinzoom);

    void UpdateFrustrum();

    // Cached variables (remain valid while the above do not change)
    Box m_frustrum;
};

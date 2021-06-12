#include "Camera.h"
#include "InputHandler.h"
#include "Keybindings.h"

#include <easyloggingpp/easylogging++.h>

namespace {
    float Expzoom(float zoom) {
        static constexpr float kZoomScaling = 100;
        return kZoomScaling * exp(zoom);       
    }

    constexpr auto kZoomIncrement = 0.1;
}

Camera::Camera(const Point& initialPosition, int zoom, float rotation, unsigned int windowWidth, unsigned int windowHeight)
    : IMessageSubscriber()
    , m_position(initialPosition) 
    , m_zoom(zoom)
    , m_rotation(rotation)
    , m_windowWidth(windowWidth)
    , m_windowHeight(windowHeight)
    , m_frustrum()
{
    UpdateFrustrum();
}

void Camera::UpdateZoom(float changeinzoom) {
    m_zoom = m_zoom + changeinzoom;
}

void Camera::ZoomIn() {
    UpdateZoom(kZoomIncrement);
}

void Camera::ZoomOut() {
    UpdateZoom(-kZoomIncrement);
}

void Camera::OnMessage(const KeysDict& keysDown) {
    using namespace Keybindings::Navigation;
    ANTGAME_TRY_GET_KEY(keysDown, ZoomIn::kCode, ZoomIn())
    ANTGAME_TRY_GET_KEY(keysDown, ZoomOut::kCode, ZoomOut())
    ANTGAME_TRY_GET_KEY(keysDown, Right::kCode, Move(Direction::Right))
    ANTGAME_TRY_GET_KEY(keysDown, Left::kCode, Move(Direction::Left))
    ANTGAME_TRY_GET_KEY(keysDown, Up::kCode, Move(Direction::Up))
    ANTGAME_TRY_GET_KEY(keysDown, Down::kCode, Move(Direction::Down))
}

SDL_FPoint Camera::WorldToScreenTransform(const Point& point) const {
    auto o_x = m_position.get<0>();
    auto o_y = m_position.get<1>();

    auto p_x = point.get<0>();
    auto p_y = point.get<1>();

    auto s = std::sin(m_rotation);
    auto c = std::cos(m_rotation);
    auto r11 = c;
    auto r12 = -s;
    auto r21 = s;
    auto r22 = c;

    auto d_x = p_x - o_x;
    auto d_y = p_y - o_y;
    
    auto z = Expzoom(m_zoom);

    SDL_FPoint ret { 
        (r11*d_x+r21*d_y)*z, 
        (r12*d_x+r22*d_y)*z 
    };

    return ret;
}

Point Camera::ScreenToWorldTransform(const SDL_FPoint& p) const {
    auto o_x = m_position.get<0>();
    auto o_y = m_position.get<1>();

    auto s = std::sin(m_rotation);
    auto c = std::cos(m_rotation);
    auto r11 = c;
    auto r12 = -s;
    auto r21 = s;
    auto r22 = c;

    auto d_x = r11*p.x+r12*p.y;
    auto d_y = r21*p.x+r22*p.y;
    
    auto z = Expzoom(m_zoom);

    Point ret((d_x + o_x)/z, (d_y + o_y)/z);
    return ret;
}

void Camera::UpdateFrustrum() {
    auto p1 = ScreenToWorldTransform({0, 0});
    auto p2 = ScreenToWorldTransform({static_cast<float>(m_windowWidth), static_cast<float>(m_windowHeight)});
    m_frustrum = Box{p1, p2};
}

void Camera::Move(const Direction direc) {
    static constexpr float kPanSpeed = 10;
    switch(direc) {
        case Direction::Up:
            m_position.set<1>( m_position.get<1>() - kPanSpeed / Expzoom(m_zoom));
            return;
        case Direction::Down:
            m_position.set<1>( m_position.get<1>() + kPanSpeed / Expzoom(m_zoom));
            return;
        case Direction::Right:
            m_position.set<0>( m_position.get<0>() + kPanSpeed / Expzoom(m_zoom));
            return;
        case Direction::Left:
            m_position.set<0>( m_position.get<0>() - kPanSpeed / Expzoom(m_zoom));
            return;
    }
}

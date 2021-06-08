#include "Camera.h"

namespace {
    float Expzoom(float zoom) {
        return 100.0 * exp(zoom);       
    }
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

void Camera::UpdatePosition(int x, int y) {
    float panspeed = 10;
    m_position.set<0>( m_position.get<0>() + panspeed * x/Expzoom(m_zoom));
    m_position.set<1>( m_position.get<1>() + panspeed * y/Expzoom(m_zoom));
}

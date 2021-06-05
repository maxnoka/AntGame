#include "Camera.h"

#include <math.h>

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
    
    auto z = m_zoom;

    SDL_FPoint ret { 
        (r11*d_x+r21*d_y)*z, 
        (r12*d_x+r22*d_y)*z 
    };

    return ret;
}

Point Camera::ScreenToWorldTransform(const SDL_FPoint& p) const {
    // TODO

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
    
    auto z = m_zoom;

    Point ret((d_x + o_x)/z, (d_y + o_y)/z);
    return ret;
}


Box Camera::GetFrustrum() const {
    auto p1 = ScreenToWorldTransform({0, 0});
    auto p2 = ScreenToWorldTransform({static_cast<float>(m_windowWidth), static_cast<float>(m_windowHeight)});
    return Box{p1, p2};
}
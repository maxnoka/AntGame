#include <antgame/WorldObject.h>

#include <iostream>

WorldObject::WorldObject(const Point& initialPosition, const std::string& name)
    : m_position(initialPosition)
    , m_id(name)
{ }

std::string WorldObject::Print(bool toCout) const {
    std::stringstream ss;
    ss << m_id << ": pos:" << boost::geometry::wkt<Point>(m_position) << std::endl;
    
    if (toCout) {
        std::cout << ss.str();
    }
    return ss.str();
}

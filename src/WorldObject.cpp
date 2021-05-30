#include <antgame/WorldObject.h>

#include <easyloggingpp/easylogging++.h>

#include <iostream>

WorldObject::WorldObject(const Point& initialPosition, const std::string& name)
    : m_position(initialPosition)
    , m_id(name)
{ }

std::string WorldObject::Print(bool toLog) const {
    std::stringstream ss;
    ss << m_id << ": pos:" << boost::geometry::wkt<Point>(m_position);
    if (toLog) {
        LOG(INFO) << ss.str();
    }
    return ss.str();
}

#pragma once

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>

#include <string>
#include <memory>

using Point =  boost::geometry::model::point<float, 2, boost::geometry::cs::cartesian>;

class WorldObject {
public:
    WorldObject(const Point& initialPosition, const std::string& name);
    
    std::string Print(bool toCout) const;
    
    /* For registering the World Object as a Point */
    float GetPosX() const { return m_position.get<0>(); }
    float GetPosY() const { return m_position.get<1>(); }
    void SetPosX(float x) { m_position.set<0>(x); }
    void SetPosY(float y) { m_position.set<1>(y); }
private:
    Point m_position;
    std::string m_id;
};

BOOST_GEOMETRY_REGISTER_POINT_2D_GET_SET(
    WorldObject,
    float,
    boost::geometry::cs::cartesian,
    GetPosX,
    GetPosY,
    SetPosX,
    SetPosY
)

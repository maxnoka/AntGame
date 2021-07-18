#pragma once
#include "Visitee.h"

#include <boost/geometry/geometries/register/point.hpp>

#include <string>
#include <memory>

class WorldTree;

class WorldObject
 : public Visitee
 , public std::enable_shared_from_this<WorldObject> {
public:
    WorldObject(const Point& initialPosition, const std::string& name);
    
    std::string Print(bool toLog) const;
    std::string GetName() const { return m_id; }

    void AttachTo(WorldTree* wt) { m_worldTree = wt; }
    
    /* For registering the World Object as a Point */
    Point GetPosition() const { return m_position; }
    float GetPosX() const { return m_position.get<0>(); }
    float GetPosY() const { return m_position.get<1>(); }
    void SetPosX(float x);
    void SetPosY(float y);

protected:
    Point m_position;
private:
    std::string m_id;
    WorldTree* m_worldTree;
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

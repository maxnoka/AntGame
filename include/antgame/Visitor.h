#pragma once

#include <boost/geometry.hpp>
#include <type_traits>

using Point = boost::geometry::model::point<float, 2, boost::geometry::cs::cartesian>;
using Box = boost::geometry::model::box<Point>;

class Ant;
class Plant;
class WorldObject;

class Visitor {
public:
    virtual void Visit(const Ant& visitee) const = 0;
    virtual void Visit(const Plant& visitee) const = 0;
    virtual void Visit(const WorldObject& visitee) const = 0;
    virtual void Visit(const Box& visitee) const = 0;
};

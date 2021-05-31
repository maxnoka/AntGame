#pragma once

#include "WorldObject.h"

#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>

#include <string>
#include <vector>
#include <memory>

namespace boost::geometry::index {
template <typename T>
struct indexable< std::shared_ptr<T>> {
    typedef std::shared_ptr<T> V;
    typedef T const& result_type;
    result_type operator()(V const& v) const { return *v; }
};
}

class WorldTree {
public:
    WorldTree();
    
    void InsertObject(const std::shared_ptr<WorldObject>& pObj);
    void RemoveObject(const std::shared_ptr<WorldObject>& pObj);
    
    std::vector<std::shared_ptr<WorldObject>> GetNearestNeighbours(const Point& point, unsigned int N) const;
    
private:
    boost::geometry::index::rtree< std::shared_ptr<WorldObject>, boost::geometry::index::quadratic<16>> m_rtree;
};

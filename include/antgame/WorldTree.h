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
    using WorldObjectRTree = boost::geometry::index::rtree< std::shared_ptr<WorldObject>, boost::geometry::index::quadratic<7>>;

    WorldTree();

    const WorldObjectRTree& GetRTree() const { return m_rtree; }
    
    void InsertObject(std::shared_ptr<WorldObject> pObj);
    void RemoveObject(std::shared_ptr<WorldObject> pObj);

    using QueryPredicate = bool (*)(const std::shared_ptr<WorldObject>&);

    auto Query(const QueryPredicate predicate) const { return m_rtree.qbegin(boost::geometry::index::satisfies(predicate)); }
    auto QueryBox(const Box& box) const { return m_rtree.qbegin(boost::geometry::index::intersects(box)); }

    auto QAll() const { return Query( [](const std::shared_ptr<WorldObject>&){ return true; } ); }
    auto QEnd() const { return m_rtree.qend(); }

    std::vector<std::shared_ptr<WorldObject>> Get(const QueryPredicate predicate) const;
    std::vector<std::shared_ptr<WorldObject>> GetAll() const;

    std::vector<std::shared_ptr<WorldObject>> GetNearestNeighbours(const Point& point, unsigned int N) const;
    
private:
    WorldObjectRTree m_rtree;
};

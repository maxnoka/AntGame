#include "inc/WorldTree.h"

WorldTree::WorldTree()
    : m_rtree()
{ }

std::vector<std::shared_ptr<WorldObject>> WorldTree::GetNearestNeighbours(const Point& point, unsigned int N) const {
    // find 5 nearest values to a point
    std::vector<std::shared_ptr<WorldObject>> result_n;
    m_rtree.query(boost::geometry::index::nearest(point, N), std::back_inserter(result_n));
    return result_n;
}

void WorldTree::InsertObject(const std::shared_ptr<WorldObject>& pObj) {
    m_rtree.insert(pObj);
}

void WorldTree::RemoveObject(const std::shared_ptr<WorldObject>& pObj) {
    m_rtree.remove(pObj);
}
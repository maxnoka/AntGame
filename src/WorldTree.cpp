#include <antgame/WorldTree.h>

WorldTree::WorldTree()
    : m_rtree()
{ }

std::vector<std::shared_ptr<WorldObject>> WorldTree::GetNearestNeighbours(const Point& point, unsigned int N) const {
    // find 5 nearest values to a point
    std::vector<std::shared_ptr<WorldObject>> result_n;
    m_rtree.query(boost::geometry::index::nearest(point, N), std::back_inserter(result_n));
    return result_n;
}

void WorldTree::InsertObject(std::shared_ptr<WorldObject> pObj) {
    m_rtree.insert(pObj);
}

void WorldTree::RemoveObject(std::shared_ptr<WorldObject> pObj) {
    m_rtree.remove(pObj);
}

std::vector<std::shared_ptr<WorldObject>> WorldTree::Get(const QueryPredicate predicate) const {
    std::vector<std::shared_ptr<WorldObject>> out;
    m_rtree.query(boost::geometry::index::satisfies(predicate), std::back_inserter(out));
    return out;
}

std::vector<std::shared_ptr<WorldObject>> WorldTree::GetAll() const {
    std::vector<std::shared_ptr<WorldObject>> out(m_rtree.size());
    m_rtree.query(
        boost::geometry::index::satisfies(
           [](const std::shared_ptr<WorldObject>&){ return true; }
        ),
        out.begin()
    );
    return out;
};
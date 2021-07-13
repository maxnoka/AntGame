#include <antgame/WorldObject.h>
#include <antgame/WorldTree.h>

#include <easyloggingpp/easylogging++.h>

#include <iostream>

WorldObject::WorldObject(const Point& initialPosition, const std::string& name)
    : m_position(initialPosition)
    , m_id(name)
    , m_worldTree(nullptr)
{ }

std::string WorldObject::Print(bool toLog) const {
    std::stringstream ss;
    ss << m_id << ": pos:" << boost::geometry::wkt<Point>(m_position);
    if (toLog) {
        LOG(INFO) << ss.str();
    }
    return ss.str();
}

void WorldObject::SetPosX(float x) { 
    const auto worldTreeBackup = m_worldTree;
    if (worldTreeBackup) {
        m_worldTree->RemoveObject(shared_from_this());
    }
    m_position.set<0>(x); 
    if (worldTreeBackup) {
        AttachTo(worldTreeBackup);
        m_worldTree->InsertObject(shared_from_this());
    }
}
void WorldObject::SetPosY(float y) {
    const auto worldTreeBackup = m_worldTree;
    if (worldTreeBackup) {
        m_worldTree->RemoveObject(shared_from_this());
    }
    m_position.set<1>(y); 
    if (worldTreeBackup) {
        AttachTo(worldTreeBackup);
        m_worldTree->InsertObject(shared_from_this());
    }
}

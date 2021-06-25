#include <antgame/World.h>

void World::AddObject(const std::shared_ptr<WorldObject>& pWorldObject) {
    m_worldTree.InsertObject(pWorldObject);
}

void World::AddAgent(const std::shared_ptr<Agent>& pAgent) {
    m_agents.push_back(pAgent);
    AddObject(pAgent);
}

void World::Update() {
    for (auto &agent : m_agents) {
        agent->Update(m_worldTree);
        // TODO Make sure world tree updates if agent has moved
    }
}

void World::DbgPrint() {
    for (auto &agent : m_agents) {
        agent->Print(true);
    }
}

/*
void WorldTree::RemoveObject(const std::shared_ptr<WorldObject>& pObj) {
    m_rtree.remove(pObj);
}
*/

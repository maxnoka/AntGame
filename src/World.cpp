#include <antgame/World.h>

void World::AddObject(const std::shared_ptr<Agent>& pAgent) {
    m_agents.push_back(pAgent);
    m_worldTree.InsertObject(pAgent);
}

void World::Update() {
    for (auto &agent : m_agents) {
        agent->Update();
        // TODO Make sure world tree updates if agent has moved
    }
}

void World::DbgPrint() {
    for (auto &agent : m_agents) {
        agent->Print(true);
        // TODO Make sure world tree updates if agent has moved
    }
}
/*
void WorldTree::RemoveObject(const std::shared_ptr<WorldObject>& pObj) {
    m_rtree.remove(pObj);
}
*/
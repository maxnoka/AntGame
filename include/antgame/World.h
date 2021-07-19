#pragma once

#include "Agent.h"
#include "WorldTree.h"

#include <vector>

class World {
public:
    World() = default;

    void FlushQueues();

    void QueueAddAgent(std::shared_ptr<Agent> pAgent);
    void QueueRemoveAgent(std::shared_ptr<Agent> pAgent);

    void AddObject(std::shared_ptr<WorldObject> pWorldObject);
    void RemoveObject(std::shared_ptr<WorldObject> pWorldObject); 

    WorldTree& GetWorldTree() { return m_worldTree; }

    auto GetObjects(const Box& box) const { return std::make_pair(m_worldTree.QueryBox(box), m_worldTree.QEnd()); }

    void Update();

    void DbgPrint();

private:
    WorldTree m_worldTree;
    std::vector<std::shared_ptr<Agent>> m_agents;

    std::vector<std::shared_ptr<Agent>> m_addQueue;
    std::vector<std::shared_ptr<Agent>> m_removeQueue;

    void AddAgent(std::shared_ptr<Agent> pAgent);
    void RemoveAgent(std::shared_ptr<Agent> pAgent);
};

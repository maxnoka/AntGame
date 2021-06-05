#pragma once

#include "Agent.h"
#include "WorldTree.h"

#include <vector>

class World {
public:
    World() = default;
    
    void AddObject(const std::shared_ptr<Agent>& pAgent);

    /*
    void RemoveObject(const std::shared_ptr<WorldObject>& pObj); 
    */

   auto GetObjects(const Box& box) { return std::make_pair(m_worldTree.QueryBox(box), m_worldTree.QEnd()); }

   void Update();

   void DbgPrint();

private:
    WorldTree m_worldTree;
    std::vector<std::shared_ptr<Agent>> m_agents;
};

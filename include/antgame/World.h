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

   void Update();

   void DbgPrint();

private:
    WorldTree m_worldTree;
    std::vector<std::shared_ptr<Agent>> m_agents;
};

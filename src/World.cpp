#include <antgame/World.h>
#include <antgame/Food.h>
#include <antgame/Ant.h>

#include <easyloggingpp/easylogging++.h>

#include <random>

void World::AddObject(std::shared_ptr<WorldObject> pWorldObject) {
    pWorldObject->AttachTo(this);
    m_worldTree.InsertObject(pWorldObject);
}

void World::AddAgent(std::shared_ptr<Agent> pAgent) {
    AddObject(pAgent);
    m_agents.push_back(pAgent);
}

void World::RemoveObject(std::shared_ptr<WorldObject> pWorldObject) {
    pWorldObject->AttachTo(nullptr);
    m_worldTree.RemoveObject(pWorldObject);
}

void World::QueueAddAgent(std::shared_ptr<Agent> pAgent) {
    m_addQueue.push_back(pAgent);
}

void World::QueueRemoveAgent(std::shared_ptr<Agent> pAgent) {
    m_removeQueue.push_back(pAgent);
}

void World::RemoveAgent(std::shared_ptr<Agent> pAgent) {
    auto search = std::find(m_agents.begin(), m_agents.end(), pAgent);
    if (search != m_agents.end()) {
        m_agents.erase(search);
    }

    RemoveObject(pAgent);
}

void World::Update() {
    static size_t updateCount = 0;
    FlushQueues();

    for (auto &agent : m_agents) {
        agent->Update(m_worldTree);
    }
    ++updateCount;

    if ((updateCount % 1000 ) == 0) {
        double averageSpeed = 0;
        double averageStarginEnergy = 0;
        size_t numAnts = 0;
        for (const auto &agent : m_agents) {
            auto pAnt = dynamic_cast<Ant*>(agent.get());
            if (pAnt) {
                averageSpeed += pAnt->GetSpeed().GetVal(); 
                averageStarginEnergy += pAnt->GetStartingEnergy().GetVal(); 
                ++numAnts;
            }
        }

        LOG(INFO) << "Average speed of ants: " << averageSpeed / numAnts;
        LOG(INFO) << "Average starting energy of ants: " << averageStarginEnergy / numAnts;
    }
}

void World::DbgPrint() {
    for (auto &agent : m_agents) {
        agent->Print(true);
    }
}
 
void World::FlushQueues() {
    for (auto& agent : m_addQueue) {
        AddAgent(agent);
    }
    m_addQueue.clear();
    for (auto& agent : m_removeQueue) {
        RemoveAgent(agent);
    }
    m_removeQueue.clear();
}

/*
void WorldTree::RemoveObject(const std::shared_ptr<WorldObject>& pObj) {
    m_rtree.remove(pObj);
}
*/

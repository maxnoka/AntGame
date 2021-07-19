#include <antgame/World.h>

void Agent::RemoveSelfFromWorld() {
    m_world->QueueRemoveAgent(std::dynamic_pointer_cast<Agent>(shared_from_this())); 
};

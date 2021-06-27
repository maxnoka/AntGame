#pragma once

#include "WorldObject.h"
#include "Visitee.h"

class WorldTree;

class Agent : public WorldObject {
public:
	Agent(const Point& initialPosition, const std::string& name) //birth of agent
	: WorldObject(initialPosition, name)
    {}

	virtual void Update(const WorldTree& world) = 0;
};

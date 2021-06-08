#pragma once

#include "WorldObject.h"

class Agent : public WorldObject {
public:
	Agent(const Point& initialPosition, const std::string& name) //birth of agent
	: WorldObject(initialPosition, name)
    {}

	virtual void Update() = 0;
};

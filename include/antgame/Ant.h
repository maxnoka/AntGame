#pragma once

#include "Agent.h"

class Ant : public Agent
{
public:
	Ant(const Point& initialPosition, const std::string& name) //birth of ant
	: Agent(initialPosition, name)
    {}
	
	void Update() override;
};

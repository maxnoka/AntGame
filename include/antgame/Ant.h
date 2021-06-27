#pragma once

#include "Agent.h"
#include "Visitee.h"

class Ant : public Agent {
public:
	Ant(const Point& initialPosition, const std::string& name) //birth of ant
	: Agent(initialPosition, name)
    {}
	
	void Update(const WorldTree& world) override;

    virtual void Accept(const Visitor& visitor) override final { visitor.Visit(*this); }
};

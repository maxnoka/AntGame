#ifndef FAUNA_H
#define FAUNA_H

#include "Agent.h"

class Ant : public Agent
{
public:
	Ant(const Point& initialPosition, const std::string& name) //birth of ant
	: Agent(initialPosition, name)
    {}
	
	void Update() override;
};


#endif // FAUNA_H

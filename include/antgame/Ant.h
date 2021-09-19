#pragma once

#include "Agent.h"
#include "Visitee.h"
#include "HeritableTrait.h"

class Food;

class Ant : public Agent {
public:
	Ant(const Point& initialPosition, const std::string& name);
	Ant(const Point& initialPosition, const std::string& name, const HeritableTrait& startingSpeed, const HeritableTrait& startingEnergy);
	
	void Update(const WorldTree& world) override;
	void Eat(Food& food);

	float GetEnergy() const { return m_energy; }
	const HeritableTrait& GetSpeed() const { return m_speed; }
	const HeritableTrait& GetStartingEnergy() const { return m_startingEnergy; }

    virtual void Accept(const Visitor& visitor) const override final { visitor.Visit(*this); }

private:
	void AddEnergy(float energy) { m_energy += energy; };

	HeritableTrait m_speed;
	HeritableTrait m_startingEnergy;
	float m_energy;
};

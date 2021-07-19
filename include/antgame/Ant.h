#pragma once

#include "Agent.h"
#include "Visitee.h"

class Food;

class Ant : public Agent {
public:
	Ant(const Point& initialPosition, const std::string& name);
	
	void Update(const WorldTree& world) override;
	void Eat(Food& food);

	float GetEnergy() const { return m_energy; }

    virtual void Accept(const Visitor& visitor) const override final { visitor.Visit(*this); }

private:
	void AddEnergy(float energy) { m_energy += energy; };

	float m_energy;
};

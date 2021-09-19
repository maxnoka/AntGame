#pragma once

#include "Agent.h"
#include "Visitee.h"

class Food;

class Ant : public Agent {
public:
	Ant(const Point& initialPosition, const std::string& name);
	
	void Update(const WorldTree& world) override;
	void Eat(Food& food);
	void Move(float direction, float distance);

	float GetEnergy() const { return m_energy; }
	// direction is an angle in degrees to the x-axis
	float GetDirection() const { return m_direction; }

    virtual void Accept(const Visitor& visitor) const override final { visitor.Visit(*this); }

private:
	void AddEnergy(float energy) { m_energy += energy; };
	void Turn(float Angle);

	float m_direction;
	float m_energy;
};

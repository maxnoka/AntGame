#include <antgame/Ant.h>
#include <antgame/Food.h>
#include <antgame/World.h>
#include <stdlib.h>

#include <easyloggingpp/easylogging++.h>

#include <boost/geometry.hpp>

namespace {

float RandFloat(float lo, float hi) {
	return lo + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(hi - lo)));
}

static constexpr auto kStartingEnergy = 100;
static constexpr auto kDivideEnergy = 200;

}

Ant::Ant(const Point& initialPosition, const std::string& name)
: Agent(initialPosition, name)
, m_startingEnergy(kStartingEnergy, 10)
, m_speed(0.1, 0.01)
, m_energy(m_startingEnergy.GetVal())
{ 
}

Ant::Ant(const Point& initialPosition, const std::string& name, const HeritableTrait& startingSpeed, const HeritableTrait& startingEnergy)
: Agent(initialPosition, name)
, m_startingEnergy(startingEnergy)
, m_speed(startingSpeed)
, m_energy(m_startingEnergy.GetVal())
{
	if (m_energy >= kDivideEnergy) {
		m_energy = kDivideEnergy - 1;
	}
}

void Ant::Eat(Food& food) {
	AddEnergy(food.GetNutritionalValue());
	food.BecomeEaten();
}

void Ant::Update(const WorldTree& world) {
	static constexpr auto kDriftDelta = 0.05;
	static constexpr auto kEatingDistance = 0.2;
	static constexpr auto kEnergyDrain = 0.1;

	AddEnergy(-kEnergyDrain);

	if (m_energy < 0) {
		LOG(INFO) << "died from lack of food";
		RemoveSelfFromWorld();
		return;
	}

	if (m_energy > kDivideEnergy) {
        auto child1 = std::make_shared<Ant>(m_position, GetName() + "_1", m_speed.Mutate(), m_startingEnergy.Mutate());
        m_world->QueueAddAgent(std::move(child1));
        auto child2 = std::make_shared<Ant>(m_position, GetName() + "_2", m_speed.Mutate(), m_startingEnergy.Mutate());
        m_world->QueueAddAgent(std::move(child2));

		RemoveSelfFromWorld();
		return;
	}

    auto nearestObject =  world.GetNearestNeighbours(m_position, 2).front();

	// This is just demo activity.
	// TODO: ant brain
	if (typeid(Food) == typeid(*nearestObject.get())) {
		static constexpr auto kSpeed = 0.01;
		auto direction = this->GetPosition();
		boost::geometry::subtract_point(direction, nearestObject->GetPosition());
		auto distance = boost::geometry::strategy::distance::pythagoras().apply(m_position, nearestObject->GetPosition());
		boost::geometry::divide_value(direction, -distance);

		if (distance < kEatingDistance) {
			Eat(*dynamic_cast<Food*>(nearestObject.get()));
		}
		else {
			this->SetPosX(this->GetPosX() + direction.get<0>() * kSpeed);
			this->SetPosY(this->GetPosY() + direction.get<1>() * kSpeed);
		}

	}

	this->SetPosX(this->GetPosX() + RandFloat(-kDriftDelta, kDriftDelta));
	this->SetPosY(this->GetPosY() + RandFloat(-kDriftDelta, kDriftDelta));
}

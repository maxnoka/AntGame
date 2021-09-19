#include <antgame/Ant.h>
#include <antgame/Food.h>
#include <antgame/World.h>

#include <easyloggingpp/easylogging++.h>

#include <boost/math/constants/constants.hpp>
#include <boost/geometry.hpp>

#include <math.h>
#include <stdlib.h>

namespace {
	float RandFloat(float lo, float hi) {
		return lo + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(hi - lo)));
	}

	inline float DegreesToRadians(float degrees) {
		return degrees * boost::math::constants::pi<double>() / 180;
	}

	static constexpr auto kStartingEnergy = 100;
}

Ant::Ant(const Point& initialPosition, const std::string& name)
: Agent(initialPosition, name)
, m_direction(RandFloat(-180, 180))
, m_energy(kStartingEnergy)
{ }

void Ant::Turn(float Angle) { //updates direction of Ant
	m_direction += Angle;

	// if (m_direction < -180){
	// 	m_direction += 360;
	// }
	// else if (m_direction > 180) {
	// 	m_direction -= 360;
	// }
}

void Ant::Move(float turningAngle, float distanceForward) {
	Ant::Turn(turningAngle);
	this->SetPosX(this->GetPosX() + (distanceForward * cos(DegreesToRadians(m_direction)))); //move forward in new direction
	this->SetPosY(this->GetPosY() + (distanceForward * sin(DegreesToRadians(m_direction))));
}

void Ant::Eat(Food& food) {
	AddEnergy(food.GetNutritionalValue());
	food.BecomeEaten();
}

void Ant::Update(const WorldTree& world) {
	static constexpr auto kDriftDelta = 0.05;
	static constexpr auto kEatingDistance = 0.2;
	static constexpr auto kDivideEnergy = 200;
	static constexpr auto kEnergyDrain = 0.1;
	static constexpr auto kMaxTurnAngle = 10;
	static constexpr auto kSpeed = 0.01; //ant speed
	static constexpr auto kVisionDistance = 200 * kSpeed; //ant speed

	AddEnergy(-kEnergyDrain);

	if (m_energy < 0) {
		LOG(INFO) << "died from lack of food";
		RemoveSelfFromWorld();
		return;
	}

	if (m_energy > kDivideEnergy) {
        auto child1 = std::make_shared<Ant>(m_position, GetName() + "_1");
        m_world->QueueAddAgent(std::move(child1));
        auto child2 = std::make_shared<Ant>(m_position, GetName() + "_2");
        m_world->QueueAddAgent(std::move(child2));

		RemoveSelfFromWorld();
		return;
	}

    auto nearestObject =  world.GetNearestNeighbours(m_position, 2).front();

	// This is just demo activity.
	// TODO: ant brain
	if (typeid(Food) == typeid(*nearestObject.get())) {
		
		auto direction = this->GetPosition(); //gets ants current position
		boost::geometry::subtract_point(direction, nearestObject->GetPosition()); //p1 - p2 = p21 a vector from the food to the ant
		auto distance = boost::geometry::strategy::distance::pythagoras().apply(m_position, nearestObject->GetPosition()); // distance to food

		if(distance < kVisionDistance) { //if you see food but it's too far away you don't see it sike
			boost::geometry::divide_value(direction, -distance); //normalises and  flips the vector to point from ant to food
			
			float angleToTurn;
			if (direction.get<0>() >= 0) {
				angleToTurn = DegreesToRadians(atan(direction.get<1>()/direction.get<0>())) - m_direction;
			}
			else if (direction.get<1>() >= 0){
				angleToTurn = 180 - DegreesToRadians(atan(direction.get<1>()/direction.get<0>())) - m_direction;
			}
			else {
				angleToTurn = -180 + DegreesToRadians(atan(direction.get<1>()/direction.get<0>())) - m_direction;
			}

			if (angleToTurn > kMaxTurnAngle) {
				angleToTurn = kMaxTurnAngle;
			}
			else if (angleToTurn < -kMaxTurnAngle) {
				angleToTurn = -kMaxTurnAngle;
			}

			if (distance < kEatingDistance) {
				Eat(*dynamic_cast<Food*>(nearestObject.get()));
			}
			else {
				Ant::Move(angleToTurn, kSpeed);
			}
		}
		else {
			Ant::Move(RandFloat(-kMaxTurnAngle, kMaxTurnAngle), kSpeed);
		}
	}
	else {
		Ant::Move(RandFloat(-kMaxTurnAngle, kMaxTurnAngle), RandFloat(kSpeed, kSpeed*2));
	}
}

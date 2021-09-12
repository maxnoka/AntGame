#include <antgame/Ant.h>
#include <antgame/Food.h>
#include <antgame/World.h>
#include <stdlib.h>
#include <math.h>

#include <easyloggingpp/easylogging++.h>

#include <boost/geometry.hpp>


#define PI 3.14159265
namespace {

float RandFloat(float lo, float hi) {
	return lo + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(hi - lo)));
}

static constexpr auto kStartingEnergy = 100;
auto kStartingDirection = RandFloat(-180, 180);

}

Ant::Ant(const Point& initialPosition, const std::string& name)
: Agent(initialPosition, name)
, m_direction(kStartingDirection)
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
	//printf("%f\n", m_direction);
	this->SetPosX(this->GetPosX() + (distanceForward * cos(m_direction*PI/180))); //move forward in new direction
	this->SetPosY(this->GetPosY() + (distanceForward * sin(m_direction*PI/180)));
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
	static constexpr auto kMaxTurnAngle = 30;
	static constexpr auto kSpeed = 0.01; //ant speed

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
		boost::geometry::divide_value(direction, -distance); //normalises and  flips the vector to point from ant to food

		float angleToTurn;

		if (direction.get<0>() >= 0) {
			angleToTurn = (atan(direction.get<1>()/direction.get<0>())*180/PI) - m_direction;
		}
		else if (direction.get<1>() >= 0){
			angleToTurn = 180 - (atan(direction.get<1>()/direction.get<0>())*180/PI) - m_direction;
		}
		else {
			angleToTurn = -180 + (atan(direction.get<1>()/direction.get<0>())*180/PI) - m_direction;
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

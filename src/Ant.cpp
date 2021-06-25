#include <antgame/Ant.h>
#include <antgame/Plant.h>
#include <antgame/WorldTree.h>
#include <stdlib.h>

#include <easyloggingpp/easylogging++.h>

#include <boost/geometry.hpp>

float RandFloat(float lo, float hi) {
	return lo + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(hi - lo)));
}

void Ant::Update(const WorldTree& world) {
	static constexpr auto driftDelta = 0.05;

    auto nearestObject =  world.GetNearestNeighbours(m_position, 2).front();

	// This is just demo activity.
	// TODO: ant brain
	if (typeid(Plant) == typeid(*nearestObject.get())) {
		static constexpr auto kSpeed = 0.01;
		auto direction = this->GetPosition();
		boost::geometry::subtract_point(direction, nearestObject->GetPosition());
		auto distance = boost::geometry::strategy::distance::pythagoras().apply(m_position, nearestObject->GetPosition());
		boost::geometry::divide_value(direction, -distance);

		this->SetPosX(this->GetPosX() + direction.get<0>() * kSpeed);
		this->SetPosY(this->GetPosY() + direction.get<1>() * kSpeed);
	}

	this->SetPosX(this->GetPosX() + RandFloat(-driftDelta, driftDelta));
	this->SetPosY(this->GetPosY() + RandFloat(-driftDelta, driftDelta));
}

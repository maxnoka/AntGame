#include <antgame/Ant.h>
#include <stdlib.h>

float RandFloat(float lo, float hi) {
	return lo + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(hi - lo)));
}

void Ant::Update() {
	static constexpr auto driftDelta = 0.01;

	this->SetPosX(this->GetPosX() + RandFloat(-driftDelta, driftDelta));
	this->SetPosY(this->GetPosY() + RandFloat(-driftDelta, driftDelta));
}

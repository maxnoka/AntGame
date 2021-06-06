#include <antgame/Ant.h>
#include <stdlib.h>

float randfloat(float LO, float HI) {
	
	float r3 = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
	return r3;
}

void Ant::Update() {
	this->SetPosX(this->GetPosX() + randfloat(-0.1, 0.1));
	this->SetPosY(this->GetPosY() + randfloat(-0.1, 0.1));
}
#pragma once

#include "Agent.h"
#include "Visitee.h"

#include <random>

class FoodSource : public Agent {
public:
    // rate is the average food items generated per step
    // size is the width and height of the box within which food is generated
	FoodSource(
        const Point& position,
        const std::string& name,
        double rate, 
        unsigned int size)
	: Agent(position, name)
    , m_rate(rate)
    , m_size(size)
    , m_numFood(0)
    , m_poissonDist(m_rate)
    , m_uniformDistX(GetPosX() - m_size, GetPosX() + m_size)
    , m_uniformDistY(GetPosY() - m_size, GetPosY() + m_size)
    {}

	void Update(const WorldTree& world) override;

    void ReportEaten() { --m_numFood; }

    virtual void Accept(const Visitor& visitor) const override final { visitor.Visit(*this); } 

private:
    double m_rate;
    unsigned int m_size;
    size_t m_numFood;
    std::poisson_distribution<int> m_poissonDist;
    std::uniform_real_distribution<double> m_uniformDistX;
    std::uniform_real_distribution<double> m_uniformDistY;

};

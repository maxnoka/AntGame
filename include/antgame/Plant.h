#pragma once

#include "WorldObject.h"
#include "Visitee.h"

class Plant : public WorldObject {
public:
	Plant(
        const Point& initialPosition,
        const std::string& name,
        int nutritionalValue)
	: WorldObject(initialPosition, name)
    , m_nutritionalValue(nutritionalValue)
    {}

    virtual void Accept(const Visitor& visitor) override final { visitor.Visit(*this); }

private:
    int m_nutritionalValue;
};

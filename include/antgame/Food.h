#pragma once

#include "WorldObject.h"
#include "Visitee.h"

#include <optional>

class FoodSource;

class Food : public WorldObject {
public:
	Food(
        const Point& initialPosition,
        const std::string& name,
        int nutritionalValue)
	: WorldObject(initialPosition, name)
    , m_nutritionalValue(nutritionalValue)
    , m_foodSource(std::nullopt)
    { }

	Food(
        const Point& initialPosition,
        const std::string& name,
        int nutritionalValue, 
        FoodSource* foodSource)
	: WorldObject(initialPosition, name)
    , m_nutritionalValue(nutritionalValue)
    , m_foodSource(foodSource)
    { }

    int GetNutritionalValue() const { return m_nutritionalValue; }
    void BecomeEaten();

    virtual void Accept(const Visitor& visitor) const override final { visitor.Visit(*this); } 

private:
    int m_nutritionalValue;
    std::optional<FoodSource*> m_foodSource;
};

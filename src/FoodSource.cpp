#include <antgame/FoodSource.h>
#include <antgame/Food.h>
#include <antgame/World.h>

#include <easyloggingpp/easylogging++.h>

#include <boost/geometry.hpp>

#include <random>

void FoodSource::Update(const WorldTree& world) {
    static std::default_random_engine generator;
    static size_t totalFoodCounter = 0;
    static constexpr auto kFoodValue = 20;
    static constexpr auto kMaxFood = 500;

    int numberOfFood = m_poissonDist(generator);
    m_numFood += numberOfFood;

    if (m_numFood > kMaxFood) {
        return;
    }

    for (size_t i = 0; i < numberOfFood; ++i) {
        auto x = m_uniformDistX(generator);
        auto y = m_uniformDistY(generator);
        Point point(x, y);
        auto newObj = std::make_shared<Food>(point, "Food_" + std::to_string(totalFoodCounter), kFoodValue, this);
        m_world->AddObject(std::move(newObj));
    }
}

#include <antgame/HeritableTrait.h>

#include <random>

HeritableTrait HeritableTrait::Mutate() const {
    static std::default_random_engine generator;
    std::normal_distribution<double> distribution(m_traitValue, m_deviation);
    const auto m_mutatedTraitValue = distribution(generator);
    return HeritableTrait(m_mutatedTraitValue, m_deviation);
}

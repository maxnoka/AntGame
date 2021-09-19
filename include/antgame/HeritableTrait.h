#include <random>

class HeritableTrait {
public:
    HeritableTrait(double value, double deviation)
    : m_traitValue(value)
    , m_deviation(deviation)
    { }

    double GetVal() const { return m_traitValue; }
    HeritableTrait Mutate() const;

private:
    double m_traitValue;
    double m_deviation;
};

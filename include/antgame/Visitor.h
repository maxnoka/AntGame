#pragma once

#include <type_traits>

class Ant;
class Plant;

class Visitor {
public:
    virtual void Visit(const Ant& visitee) const = 0;
    virtual void Visit(const Plant& visitee) const = 0;
};

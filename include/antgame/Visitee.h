#pragma once

#include "Visitor.h"

class Visitee {
public:
    virtual void Accept(const Visitor& visitor) const = 0;
};

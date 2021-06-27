#pragma once

#include "Visitor.h"

class Visitee {
public:
    virtual void Accept(const Visitor& visitor) = 0;
};

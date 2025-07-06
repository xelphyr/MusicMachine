#pragma once

#include "blocks/internal/ports/port.hpp"

class PortIn : public Port
{
public:
    virtual bool isReady() = 0;
    virtual void Reset() = 0;
};
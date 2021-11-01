#include "Unit.h"

Unit::Unit(){}

Unit::Unit(oxygine::Vector2 tPosition, oxygine::Vector2 tSize)
{
    gPosition = tPosition;
    gSize = tSize;
}

Unit::~Unit(){}
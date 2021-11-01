#pragma once
#include "../framework/oxygine/src/oxygine-framework.h"
class Unit
{
protected:
    oxygine::Vector2 gPosition{0.0f, 0.0f};
    oxygine::Vector2 gSize{0.05f, 0.05f};
public:
    Unit();
    Unit(oxygine::Vector2 tPosition, oxygine::Vector2 tSize = oxygine::Vector2{0.05f, 0.05f});
    virtual ~Unit();
};
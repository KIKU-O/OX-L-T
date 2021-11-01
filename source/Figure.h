#pragma once
#include "Object.h"

class Figure : public Object
{

public:
    unsigned int gMoved = 0;
    bool gDestroyed = false;
    bool gFree = false;
public:
    Figure();
    Figure(const std::string& tName, const oxygine::Resources& tResources, const oxygine::Vector2& tPosition, const oxygine::Vector2& tSize = oxygine::Vector2{0.05f, 0.05f}, Figure::Color tColor = Figure::Color::BLACK);
    void Destroy();
    ~Figure();
};
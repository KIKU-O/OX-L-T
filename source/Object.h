#pragma once
#include "Unit.h"
#include "../framework/oxygine/src/oxygine-framework.h"
class Object : public oxygine::Actor, public Unit
{
public:
    Object();
    ~Object();
    oxygine::spSprite& Sprite();
    enum Color
    {
        WHITE,
        BLACK
    } gColor = Color::BLACK;
    bool gSelected = false;
protected:
    void Clicked(oxygine::Event* tEvent);
    void Over(oxygine::Event* tEvent);
    oxygine::spSprite gSprite{};
};
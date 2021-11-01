#include "Object.h"

Object::Object(){}

Object::~Object(){}

oxygine::spSprite& Object::Sprite()
{
    return gSprite;
}

void Object::Clicked(oxygine::Event* tEvent)
{
    gSelected = true;
}

void Object::Over(oxygine::Event* tEvent)
{
    if (tEvent->type == oxygine::TouchEvent::OVER)
    {
        gSprite->addTween(oxygine::Sprite::TweenAddColor(oxygine::Color(128, 128, 64, 0)), 300);
    }

    if (tEvent->type == oxygine::TouchEvent::OUTX)
    {
        gSprite->addTween(oxygine::Sprite::TweenAddColor(oxygine::Color(0, 0, 0, 0)), 300);
    }
}
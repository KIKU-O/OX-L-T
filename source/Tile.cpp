#include "Tile.h"

Tile::Tile(const std::string& tName, const oxygine::Resources& tResources, const oxygine::Vector2& tOffset, const oxygine::Vector2& tSize, Tile::Color tColor, Tile::Occupation tOccupation) : ID(Counter++)
{
    gSprite = new oxygine::Sprite();
    gSprite->setResAnim(tResources.getResAnim(tName));
    this->setScale(tSize);
    gPosition = (((oxygine::getStage()->getSize() * 0.85f) - (gSprite->getSize() * 0.85f)) + tOffset);
    this->setPosition(gPosition); gSprite->setPosition(oxygine::Vector2(0.0f, 0.0f));
    this->setPriority(32);

    gColor = tColor;
    gOccupation = tOccupation;

    // Event Handling
    oxygine::EventCallback Callback = CLOSURE(this, &Tile::Clicked);
    this->addEventListener(oxygine::TouchEvent::CLICK, Callback);

    Callback = CLOSURE(this, &Tile::Over);
    this->addEventListener(oxygine::TouchEvent::OVER, Callback);
    this->addEventListener(oxygine::TouchEvent::OUTX, Callback);
    // --------------

    oxygine::Actor::addChild(gSprite);
}

unsigned int Tile::Counter = 0;

Tile::~Tile(){}
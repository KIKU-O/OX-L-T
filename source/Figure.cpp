#include "Figure.h"

Figure::Figure(){};

Figure::Figure(const std::string& tName, const oxygine::Resources& tResources, const oxygine::Vector2& tPosition, const oxygine::Vector2& tSize, Figure::Color tColor)
{
    gSprite = new oxygine::Sprite();
    gSprite->setResAnim(tResources.getResAnim(tName));
    //gSprite->setLocalScale(tSize);
    this->setScale(tSize);
    gPosition = tPosition;
    this->setPosition(gPosition); gSprite->setPosition(oxygine::Vector2(200.0f, -1000.0f)); // Correct sprite position.
    this->setPriority(64);

    gColor = tColor;

    // Event Handling
    oxygine::EventCallback Callback = CLOSURE(this, &Figure::Clicked);
    this->addEventListener(oxygine::TouchEvent::CLICK, Callback);

    Callback = CLOSURE(this, &Figure::Over);
    this->addEventListener(oxygine::TouchEvent::OVER, Callback);
    this->addEventListener(oxygine::TouchEvent::OUTX, Callback);
    // --------------

    oxygine::Actor::addChild(gSprite);
}

void Figure::Destroy()
{
    gDestroyed = true;
    this->setPriority(128);
    gSprite->addTween(oxygine::Actor::TweenAlpha(0), 600);
    if (gSprite->getAlpha() == 0)
    {
        gSprite->detach();
        this->detach();
    }
}

Figure::~Figure(){};
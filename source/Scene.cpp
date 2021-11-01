#include "Scene.h"
#include <iostream>

Scene::Scene(){}

Scene::~Scene(){}

// Helper Functions
bool isInRange(const oxygine::Vector2& A_Position, const oxygine::Vector2& B_Position, float Distance = 16.0f)
{
    return (std::fabs(A_Position.y - B_Position.y) < Distance && std::fabs(A_Position.x - B_Position.x) <= Distance);
}

bool isInRange(const oxygine::Vector2& A_Position, const oxygine::Vector2& B_Position, float Distance_A, float Distance_B)
{
    return (std::fabs(A_Position.y - B_Position.y) < Distance_A && std::fabs(A_Position.x - B_Position.x) <= Distance_B);
}

bool isTheSame(const oxygine::Vector2& A_Position, const oxygine::Vector2& B_Position)
{
    return (std::fabs(A_Position.y - B_Position.y) < 2.0f && std::fabs(A_Position.x - B_Position.x) < 2.0f); // Check if it's the same position.
}
// ----------------

void Scene::Initialize()
{
    gGrid.Initialize(gResources, gFigures);
}

void Scene::Load(const std::string& tPath)
{
    gResources.loadXML(tPath);
}

// Detect user actions. Select active objects.
void Scene::Control()
{
    // Check if user selected figure. Reset bool if so.
    for (size_t i = 0; i < gFigures.size(); i++)
    {
        if (gFigures[i]->gSelected)
        {
            if (!Turn && gFigures[i]->gColor == Object::Color::BLACK)
                Selected_Object_First = i;
            else if (Turn && gFigures[i]->gColor == Object::Color::WHITE)
                Selected_Object_First = i;

            gFigures[i]->gSelected = false;
            break;
        }

        i == Selected_Object_First ? gFigures[i]->Sprite()->setColor(oxygine::Color::Yellow) : gFigures[i]->Sprite()->setColor(oxygine::Color::White);
    }

    // Check if user selected tile. Reset bool if so.
    for (size_t i = 0; i < gGrid.gTiles.size(); i++)
    {
        if (gGrid.gTiles[i]->gSelected)
        {
            if (Selected_Object_First != -1)
            {
                Selected_Object_Second = i;
            }
            gGrid.gTiles[i]->gSelected = false;
            break;
        }

        i == Selected_Object_Second ? gGrid.gTiles[i]->Sprite()->setColor(oxygine::Color::Yellow) : gGrid.gTiles[i]->Sprite()->setColor(oxygine::Color::White);
    }
}

// Check occupation, move figures.
void Scene::Update()
{
    // If user selected figure and tile - check occupation.
    if (Selected_Object_First != -1 && Selected_Object_Second != -1)
    {
        for (size_t i = 0; i < gGrid.gTiles.size(); i++)
        {
            for (size_t j = 0; j < gFigures.size(); j++)
            {
                // Check if tile is occupied by figure.
                if (isInRange(gFigures[j]->getPosition(), gGrid.gTiles[i]->getPosition(), 4.0f))
                {
                    if (gFigures[j]->gColor == Object::Color::BLACK)
                    {
                        if (gGrid.gTiles[i]->gType == Tile::Type::TOP_EDGE)
                        {
                            gFigures[j]->gFree = true;
                        }
                        gGrid.gTiles[i]->gOccupation = Tile::Occupation::OCCUPIED_BY_BLACK;
                        break;
                    }
                    else if (gFigures[j]->gColor == Object::Color::WHITE)
                    {
                        if (gGrid.gTiles[i]->gType == Tile::Type::BOTTOM_EDGE)
                        {
                            gFigures[j]->gFree = true;
                        }
                        gGrid.gTiles[i]->gOccupation = Tile::Occupation::OCCUPIED_BY_WHITE;
                        break;
                    }
                }
                else
                {
                    // Reset
                    gGrid.gTiles[i]->gOccupation = Tile::Occupation::FREE;
                }
            }
        }

        // If travel distance is allowed and destination isn't the current position.
        if (isInRange(gFigures[Selected_Object_First]->getPosition(), gGrid.gTiles[Selected_Object_Second]->getPosition(), 64.0f, 16.0f) && !isTheSame(gFigures[Selected_Object_First]->getPosition(), gGrid.gTiles[Selected_Object_Second]->getPosition()))
        {
            switch (Turn)
            {
                case false:
                    // Black Figure Turn
                    if ((gGrid.gTiles[Selected_Object_First]->getPosition().y < gFigures[Selected_Object_First]->getPosition().y) && (gGrid.gTiles[Selected_Object_Second]->gOccupation != Tile::Occupation::OCCUPIED_BY_BLACK))
                    {
                        gFigures[Selected_Object_First]->addTween(oxygine::Actor::TweenPosition(gGrid.gTiles[Selected_Object_Second]->getPosition().x, gGrid.gTiles[Selected_Object_Second]->getPosition().y), 300);
                        gFigures[Selected_Object_First]->gMoved++;
                        Turn = !Turn;
                    }
                    break;
                case true:
                    // White Figure Turn
                    if ((gGrid.gTiles[Selected_Object_Second]->getPosition().y > gFigures[Selected_Object_First]->getPosition().y) && (gGrid.gTiles[Selected_Object_Second]->gOccupation != Tile::Occupation::OCCUPIED_BY_WHITE))
                    {
                        gFigures[Selected_Object_First]->addTween(oxygine::Actor::TweenPosition(gGrid.gTiles[Selected_Object_Second]->getPosition().x, gGrid.gTiles[Selected_Object_Second]->getPosition().y), 300);
                        gFigures[Selected_Object_First]->gMoved++;
                        Turn = !Turn;
                    }
                    break;
            }
        }

        Selected_Object_First = Selected_Object_Second = -1;
    }
}

// Detect collision, destroy figures.
void Scene::Clear()
{
    for (size_t i = 0; i < gFigures.size(); i++)
    {
        for (size_t j = 0; j < gFigures.size(); j++)
        {
            // std::fabs(gFigures[i]->gSprite->getPosition() - gFigures[j]->gSprite->getPosition()) < oxygine::Vector2(1.0f, 1.0f) ???
            if (isInRange(gFigures[i]->getPosition(), gFigures[j]->getPosition(), 0.25f))
            {
                // If isn't the same color.
                if ((gFigures[i]->gColor == Object::Color::BLACK && gFigures[j]->gColor == Object::Color::WHITE) ||
                    (gFigures[i]->gColor == Object::Color::WHITE && gFigures[j]->gColor == Object::Color::BLACK))
                {
                    //Turn ? gFigures[j]->Destroy() : gFigures[i]->Destroy();
                    if (!Turn)
                    {
                        if (!gFigures[i]->gDestroyed)
                        {
                            gFigures[j]->Destroy();
                        }
                        break;
                    }
                    else
                    {
                        if (!gFigures[j]->gDestroyed)
                        {
                            gFigures[i]->Destroy();
                        }
                        break;
                    }
                    break;
                }
            }
        }
    }
}
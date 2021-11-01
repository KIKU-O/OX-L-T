#include "Grid.h"

Grid::Grid(){}

void Grid::Initialize(const oxygine::Resources& tResources, std::vector<oxygine::intrusive_ptr<Figure>>& tFigures)
{
    const unsigned int Rows = 8;
    const oxygine::Vector2 Start = oxygine::Vector2(50.0f, 50.0f);
    oxygine::Vector2 Offset = Start; bool Turn = false;
    
    // Columns
    for (size_t i = 0; i < Rows; i++)
    {
        // Rows
        for (size_t y = 0; y < Rows; y++)
        {
            Turn ? gTiles.push_back(new Tile("White", tResources, Offset, oxygine::Vector2(0.10f, 0.10f), Object::Color::BLACK, Tile::Occupation::FREE)) : gTiles.push_back(new Tile("Black", tResources, Offset, oxygine::Vector2(0.10f, 0.10f), Object::Color::WHITE, Tile::Occupation::FREE));

            Turn = !Turn; // Change color
            Offset.x += Start.x; // Next Column
        }
        Turn = !Turn; // Start from diff. color
        Offset.x = Start.x; // Reset Column
        Offset.y += Start.y; // Next Row
    }


    for (size_t i = 0; i < gTiles.size(); i++)
    {
        // Assign Positional Flags
        if (i < (gTiles.size() * 0.10f))
        {
            gTiles[i]->gType = Tile::Type::TOP_EDGE;
        }
        else if (i >= (gTiles.size() * 0.90f))
        {
            gTiles[i]->gType = Tile::Type::BOTTOM_EDGE;
        }
        else
        {
            gTiles[i]->gType = Tile::Type::STANDART;
        }

        // Place Figures
        if (i < (gTiles.size() * 0.25f)) // White Figures
            tFigures.push_back(new Figure("Figure-White", tResources, gTiles[i]->getPosition(), oxygine::Vector2(0.05f, 0.05f), Figure::WHITE));
        else if (i >= (gTiles.size() * 0.75f)) // Black Figures
            tFigures.push_back(new Figure("Figure-Black", tResources, gTiles[i]->getPosition(), oxygine::Vector2(0.05f, 0.05f), Figure::BLACK));
    }

    for (oxygine::intrusive_ptr<Tile>& T : gTiles)
        oxygine::getStage()->addChild(T);
    for (oxygine::intrusive_ptr<Figure>& T : tFigures)
        oxygine::getStage()->addChild(T);
}

Grid::~Grid(){}
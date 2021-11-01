#pragma once
#include "Figure.h"
#include "Tile.h"
#include <array>

#include "../framework/oxygine/src/oxygine-framework.h"
class Grid
{
public:
    Grid();
    void Initialize(const oxygine::Resources& tResources, std::vector<oxygine::intrusive_ptr<Figure>>& tFigures);
    ~Grid();
public:
    std::vector<oxygine::intrusive_ptr<Tile>> gTiles{};
};
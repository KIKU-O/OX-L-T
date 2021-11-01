#pragma once
#include "Figure.h"
#include "Tile.h"
#include "Grid.h"

#include <vector>
#include <string>
#include <cmath>

#include "../framework/oxygine/src/oxygine-framework.h"

class Scene
{
public:
    Scene();
    ~Scene();

    void Initialize();
    void Load(const std::string& tPath);

    void Control();
    void Update();
    void Clear();
private:
    Grid gGrid{};
    std::vector<oxygine::intrusive_ptr<Figure>> gFigures{};
    oxygine::Resources gResources{};

    int Selected_Object_First = -1, Selected_Object_Second = -1;
    bool Turn = false; // False - black, True - white
};
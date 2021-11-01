#pragma once
#include "Scene.h"
#include "Settings.h"

#include <iostream>
#include <fstream>
#include "../framework/oxygine/src/oxygine-framework.h"

class Engine
{
public:
    Engine();
    ~Engine();
    int Process();
private:
    bool Initialize();
    Scene gScene{};
    oxygine::core::init_desc gDescription{};
};
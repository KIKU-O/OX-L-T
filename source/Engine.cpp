#include "Engine.h"

Engine::Engine(){}

Engine::~Engine(){}

bool Engine::Initialize()
{
    std::cout << "Engine Has Been Started!" << std::endl;
    gDescription.title = "Base";
    gDescription.w = APPLICATION_WIDTH;
    gDescription.h = APPLICATION_HEIGHT;
    gDescription.borderless = false;
    gDescription.vsync = APPLICATION_VSYNC; //Unlock fps
    return oxygine::core::init(&gDescription);
}

int Engine::Process()
{
    if (Engine::Initialize())
    {
        oxygine::ObjectBase::__startTracingLeaks();
        bool Done = false;

        // Stage
        oxygine::Stage::instance = new oxygine::Stage();
        oxygine::getStage()->setSize(oxygine::core::getDisplaySize());
        // -----

        //std::ifstream ft("../assets/Resources.xml");
        //if (!ft) { return -1; } // Debug
        gScene.Load("../assets/Resources.xml");
        gScene.Initialize();

        oxygine::Color gClearColor(32, 32, 32, 255);
        oxygine::Rect Viewport(oxygine::Point(0, 0), oxygine::core::getDisplaySize());

        oxygine::DebugActor::show();

        while (!Done)
        {
            // Logic
            oxygine::getStage()->update();

            gScene.Control();
            gScene.Update();
            gScene.Clear();
            // -----

            // Rendering
            if (oxygine::core::beginRendering())
            {
                oxygine::getStage()->render(gClearColor, Viewport);
                oxygine::core::swapDisplayBuffers();
            }
            // ---------

            Done = oxygine::core::update();
        }
        oxygine::ObjectBase::dumpCreatedObjects();

        oxygine::core::release();
        oxygine::ObjectBase::__stopTracingLeaks();
    }
    std::cout << "Engine Processing Has Been Finished!" << std::endl;
    return 6;
}
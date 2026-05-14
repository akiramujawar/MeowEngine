//
// Created by Akira Mujawar on 23/02/26.
//

#include <GraphicsDevice.hpp>

namespace MeowEngine::Graphics {
    GraphicsDevice::GraphicsDevice()
    : Window(Platform::SDL_EngineWindow())
    {
        MeowEngine::Log("GraphicsDevice", "Constructed");
    }

    GraphicsDevice::~GraphicsDevice() {
        MeowEngine::Log("GraphicsDevice", "Destructed");
    }

    Platform::SDL_EngineWindow& GraphicsDevice::GetWindow() {
        return Window;
    }
}

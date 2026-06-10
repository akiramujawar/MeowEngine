//
// Created by Akira Mujawar on 17/05/26.
//

#ifndef MEOWENGINE_RENDERERCONTEXT_HPP
#define MEOWENGINE_RENDERERCONTEXT_HPP

#include <GraphicsDevice.hpp>
#include <InputDevice.hpp>
#include <GameplaySystem.hpp>
#include <CommandQueue.hpp>

namespace MeowEngine::Rendering {
    struct RendererInitData {
        Graphics::GraphicsDevice* GraphicsDevice;
        Input::InputDevice* InputDevice;
        Runtime::GameplaySystem* Gameplay;
        Messaging::CommandQueue* CommandQueue;
    };
}

#endif //MEOWENGINE_RENDERERCONTEXT_HPP
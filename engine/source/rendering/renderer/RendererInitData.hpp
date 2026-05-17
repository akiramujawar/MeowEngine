//
// Created by Akira Mujawar on 17/05/26.
//

#ifndef MEOWENGINE_RENDERERCONTEXT_HPP
#define MEOWENGINE_RENDERERCONTEXT_HPP

#include <GraphicsDevice.hpp>
#include <GameplaySystem.hpp>

namespace MeowEngine::Rendering {
    struct RendererInitData {
        Graphics::GraphicsDevice* Device;
        Runtime::GameplaySystem* Gameplay;

    };
}

#endif //MEOWENGINE_RENDERERCONTEXT_HPP
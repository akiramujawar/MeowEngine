//
// Created by Akira Mujawar on 21/06/24.
//

#include <RenderSystem.hpp>
#include <log.hpp>

#include "RenderGraph.hpp"

namespace MeowEngine::Runtime::Systems {
    RenderSystem::RenderSystem(Shared::RenderGraph& graph)
    : Window(SDL_EngineWindow())
    , FrameBuffer(OpenGLFrameBuffer(1000, 500))
    , Graph(graph)
    {
        MeowEngine::Log("Scheduler", "Constructed");
    }

    RenderSystem::~RenderSystem() {
        MeowEngine::Log("Scheduler", "Destructed");
    }

    void RenderSystem::Render() {
        Graph.Build();
        Graph.Execute();
    }

}

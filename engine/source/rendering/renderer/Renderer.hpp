//
// Created by Akira Mujawar on 17/05/26.
//

#ifndef MEOWENGINE_RENDERER_HPP
#define MEOWENGINE_RENDERER_HPP

#include <Public/Threading/Include.hpp>

#include <RenderContext.hpp>
#include <SceneRenderer.hpp>
#include <UIRenderer.hpp>
#include <RenderPipelineManager.hpp>
#include <RenderResourceManager.hpp>

namespace MeowEngine::Graphics {
    class GraphicsDevice;
}


namespace MeowEngine::Rendering {
    struct RendererInitData;
    class RenderExtractor;

    class Renderer {
    public:
        Renderer();
        ~Renderer();

        void Init(RendererInitData& context);
        void SubscribeToEvents();
        void Schedule(Threading::Scheduler& scheduler);
        void Shutdown();

        RenderResourceManager& GetResourceManager() {
            return ResourceManager;
        }

    private:
        RenderContext Context;
        SceneRenderer Scene;
        UIRenderer UI;

        RenderPipelineManager PipelineManager;
        RenderResourceManager ResourceManager;

        Graphics::GraphicsDevice* GraphicsDevice;
    };
}


#endif //MEOWENGINE_RENDERER_HPP
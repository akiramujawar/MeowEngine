//
// Created by Akira Mujawar on 17/05/26.
//

#ifndef MEOWENGINE_RENDERER_HPP
#define MEOWENGINE_RENDERER_HPP

#include <Public/Threading/Include.hpp>
#include <WorldRenderer.hpp>
#include <UIRenderer.hpp>

namespace MeowEngine::Graphics {
    class GraphicsDevice;
}

namespace MeowEngine::Rendering {
    struct RendererContext;

    class Renderer {
    public:
        Renderer();
        ~Renderer();

        void Init(RendererContext& context);
        void Schedule(Threading::Scheduler& scheduler);

    private:
        WorldRenderer World;
        UIRenderer UI;

        Graphics::GraphicsDevice* Device;
    };
}


#endif //MEOWENGINE_RENDERER_HPP
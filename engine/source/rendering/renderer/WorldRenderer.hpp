//
// Created by Akira Mujawar on 13/05/26.
//

#ifndef MEOWENGINE_WORLDRENDERER_HPP
#define MEOWENGINE_WORLDRENDERER_HPP

#include <RenderGraph.hpp>
#include <GLWorldViewBuffer.hpp>

#include <RuntimeWorldBuilder.hpp>
#include <EditorWorldBuilder.hpp>

#include <Public/Threading/Forward.hpp>

namespace MeowEngine::Rendering {
    struct RendererInitData;

    /**
     * Handles the various render pipelines, passes, graphs
     */
    class WorldRenderer {
    public:
        WorldRenderer();
        ~WorldRenderer();

        void Init(RendererInitData& context);
        void Schedule(Threading::Scheduler& scheduler);

    private:
        RenderGraph RenderGraph;

        /**
         * Draws our game view onto a ui panel (which is a framebuffer)
         */
        Graphics::GLWorldViewBuffer WorldViewFrameBuffer;

        Runtime::RuntimeWorldBuilder RuntimeBuilder;
        Editor::EditorWorldBuilder EditorBuilder;
    };
}


#endif //MEOWENGINE_WORLDRENDERER_HPP
//
// Created by Akira Mujawar on 13/05/26.
//

#ifndef MEOWENGINE_RENDERSYSTEM_HPP
#define MEOWENGINE_RENDERSYSTEM_HPP

#include <RenderGraph.hpp>
#include <RuntimeRenderPipeline.hpp>
#include <EditorRenderPipeline.hpp>

#include <Threading.hpp>

namespace MeowEngine::Rendering {
    class RenderSystem {
    public:
        RenderSystem();
        ~RenderSystem();

        void Schedule(Scheduler& scheduler);

    private:
        RenderGraph RenderGraph;

        Runtime::RenderPipeline RuntimeRenderPipeline;
        Editor::RenderPipeline EditorRenderPipeline;
    };
}


#endif //MEOWENGINE_RENDERSYSTEM_HPP
//
// Created by Akira Mujawar on 13/05/26.
//

#ifndef MEOWENGINE_SCENERENDERER_HPP
#define MEOWENGINE_SCENERENDERER_HPP

#include <RenderSceneGraph.hpp>

#include <RuntimeSceneBuilder.hpp>
#include <EditorSceneBuilder.hpp>

#include <Public/Threading/Forward.hpp>

namespace MeowEngine::Rendering {
    struct RendererInitData;
    struct RenderContext;

    /**
     * Handles the various render pipelines, passes, graphs
     */
    class SceneRenderer {
    public:
        SceneRenderer();
        ~SceneRenderer();

        void Init(RendererInitData& context);
        void Schedule(Threading::Scheduler& scheduler, RenderContext& renderContext);
        void Shutdown();

    private:
        RenderSceneGraph RenderGraph;

        Runtime::RuntimeSceneBuilder RuntimeSceneBuilder;
        Editor::EditorSceneBuilder EditorSceneBuilder;
    };
}


#endif //MEOWENGINE_SCENERENDERER_HPP
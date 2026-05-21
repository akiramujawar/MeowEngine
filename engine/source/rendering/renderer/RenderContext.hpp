//
// Created by Akira Mujawar on 21/05/26.
//

#ifndef MEOWENGINE_RENDERCONTEXT_HPP
#define MEOWENGINE_RENDERCONTEXT_HPP

namespace MeowEngine::Rendering {
    class RenderPipelineManager;
    class RenderResourceManager;
    class RenderSceneData;

    struct RenderContext {
        RenderPipelineManager* PipelineManager;
        RenderResourceManager* ResourceManager;
        RenderSceneData* SceneData;
    };
}

#endif //MEOWENGINE_RENDERCONTEXT_HPP
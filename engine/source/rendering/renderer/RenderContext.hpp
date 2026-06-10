//
// Created by Akira Mujawar on 21/05/26.
//

#ifndef MEOWENGINE_RENDERCONTEXT_HPP
#define MEOWENGINE_RENDERCONTEXT_HPP

namespace MeowEngine::Rendering {
    class RenderPipelineManager;
    class RenderResourceManager;
    struct RenderSceneData;
    struct RenderUIData;

    struct RenderContext {
        RenderPipelineManager* PipelineManager;
        RenderResourceManager* ResourceManager;
        RenderSceneData* SceneData;
        RenderUIData* UIData;
    };
}

#endif //MEOWENGINE_RENDERCONTEXT_HPP
//
// Created by Akira Mujawar on 21/05/26.
//

#ifndef MEOWENGINE_RENDERCONTEXT_HPP
#define MEOWENGINE_RENDERCONTEXT_HPP

namespace MeowEngine::Messaging {
    class CommandQueue;
}

namespace MeowEngine::Rendering {
    class RenderPipelineManager;
    class RenderResourceManager;
    class RenderExtractor;
    struct RenderSceneData;
    struct RenderUIData;

    struct RenderContext {
        Messaging::CommandQueue* CommandQueue;

        RenderPipelineManager* PipelineManager;
        RenderResourceManager* ResourceManager;
        RenderExtractor* Extractor;

        RenderSceneData* SceneData;
        RenderUIData* UIData;
    };
}

#endif //MEOWENGINE_RENDERCONTEXT_HPP
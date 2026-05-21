//
// Created by Akira Mujawar on 18/05/26.
//

#ifndef MEOWENGINE_RENDERSCENEEXTRACTOR_HPP
#define MEOWENGINE_RENDERSCENEEXTRACTOR_HPP

#include <Public/Threading/Forward.hpp>
#include <RenderSceneData.hpp>
#include <RenderSceneExtractorInitData.hpp>

namespace MeowEngine::Rendering {
    class RenderResourceManager;

    /**
     * Collects & prepares ECS world for rendering
     */
    class RenderSceneExtractor {
    public:
        void Init(const RenderSceneExtractorInitData& data);
        void Schedule(Threading::Scheduler& scheduler, RenderResourceManager& resourceManager);

        DoubleBuffer<RenderSceneData>& GetRenderFrameData() {
            return RenderSceneData;
        }
    private:
        void ExtractRuntime(RenderResourceManager& resourceManager);
        void ExtractEditor(RenderResourceManager& resourceManager);

        DoubleBuffer<RenderSceneData> RenderSceneData;
        Runtime::GameplaySystem* Gameplay;
        Editor::Selector* Selector;
    };
}


#endif //MEOWENGINE_RENDERSCENEEXTRACTOR_HPP
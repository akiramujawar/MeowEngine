//
// Created by Akira Mujawar on 18/05/26.
//

#ifndef MEOWENGINE_RENDERFRAMEEXTRACTOR_HPP
#define MEOWENGINE_RENDERFRAMEEXTRACTOR_HPP

#include <Public/Threading/Forward.hpp>
#include <RenderFrameData.hpp>
#include <RenderFrameExtractorInitData.hpp>

namespace MeowEngine::Rendering {
    /**
     * Collects & prepares ECS world for rendering
     */
    class RenderFrameExtractor {
    public:
        void Init(const RenderFrameExtractorInitData& data);
        void Schedule(Threading::Scheduler& scheduler);

        DoubleBuffer<RenderFrameData>& GetRenderFrameData() {
            return RenderFrameData;
        }
    private:
        void ExtractRuntime();
        void ExtractEditor();

        DoubleBuffer<RenderFrameData> RenderFrameData;
        Runtime::GameplaySystem* Gameplay;
        Editor::Selector* Selector;
    };
}


#endif //MEOWENGINE_RENDERFRAMEEXTRACTOR_HPP
//
// Created by Akira Mujawar on 12/06/26.
//

#include <RenderExtractor.hpp>

// core
#include <Public/Threading/Include.hpp>

#include <RenderRuntimeExtractor.hpp>
#include <RenderEditorExtractor.hpp>

namespace MeowEngine::Rendering {
    RenderExtractor::RenderExtractor() {}
    RenderExtractor::~RenderExtractor() {}

    void RenderExtractor::Init(const RenderExtractorInitData& data) {
        Runtime = std::make_unique<RenderRuntimeExtractor>();
        Editor = std::make_unique<RenderEditorExtractor>();

        Runtime->Init(data);
        Editor->Init(data);
    }

    void RenderExtractor::Schedule(Threading::Scheduler& scheduler) {
        scheduler.AddTask(
            [this]() {
                PT_PROFILE_SCOPE_N("Render Extraction");

                auto& sceneFrame = GetRenderSceneData().GetWrite();
                auto& uiFrame = GetRenderUIData().GetWrite();

                Runtime->Clear(sceneFrame, uiFrame);
                Runtime->ExtractScene(sceneFrame);
                Runtime->ExtractUI(uiFrame);

                Editor->Clear(sceneFrame, uiFrame);
                Editor->ExtractScene(sceneFrame);
                Editor->ExtractUI(uiFrame);
            }
        );

        // swap buffers (internally only swaps if buffers are not locked)
        scheduler.AddTask(
            [this]() {
                PT_PROFILE_SCOPE_N("Render Extract Swap");
                RenderSceneData.Swap();
                RenderUIData.Swap();
            }
        );
    }
}

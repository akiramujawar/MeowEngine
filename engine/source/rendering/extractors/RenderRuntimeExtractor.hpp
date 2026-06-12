//
// Created by Akira Mujawar on 12/06/26.
//

#ifndef MEOWENGINE_RENDERRUNTIMEEXTRACTOR_HPP
#define MEOWENGINE_RENDERRUNTIMEEXTRACTOR_HPP

#include <IRenderExtractor.hpp>
#include <RenderExtractorInitData.hpp>

namespace MeowEngine::Rendering {
    struct RenderSceneData;
    struct RenderUIData;

    class RenderRuntimeExtractor : public IRenderExtractor {
    public:
        void Init(const RenderExtractorInitData& frame) override;

        void ExtractScene(RenderSceneData& frame) override;
        void ExtractUI(RenderUIData& frame) override;
        void Clear(RenderSceneData& sceneFrame, RenderUIData& uiFrame) override;

    private:
        Runtime::GameplaySystem* Gameplay;
        Editor::Selector* Selector;
    };
}


#endif //MEOWENGINE_RENDERRUNTIMEEXTRACTOR_HPP
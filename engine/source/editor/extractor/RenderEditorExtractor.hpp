//
// Created by Akira Mujawar on 12/06/26.
//

#ifndef MEOWENGINE_RENDEREDITOREXTRACTOR_HPP
#define MEOWENGINE_RENDEREDITOREXTRACTOR_HPP

#include <IRenderExtractor.hpp>
#include <RenderExtractorInitData.hpp>

namespace MeowEngine::Rendering {
    class RenderEditorExtractor : public IRenderExtractor {
    public:
        RenderEditorExtractor();

        void Init(const RenderExtractorInitData& context) override;

        void ExtractScene(RenderSceneData& frame) override;
        void ExtractUI(RenderUIData& frame) override;
        void Clear(RenderSceneData& sceneFrame, RenderUIData& uiFrame) override;

    private:
        Runtime::GameplaySystem* Gameplay;
        Editor::Selector* Selector;
        Asset::AssetManager* AssetManager;
    };
}

#endif //MEOWENGINE_RENDEREDITOREXTRACTOR_HPP
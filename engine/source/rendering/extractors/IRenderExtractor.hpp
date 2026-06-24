//
// Created by Akira Mujawar on 12/06/26.
//

#ifndef MEOWENGINE_IRENDEREXTRACTOR_HPP
#define MEOWENGINE_IRENDEREXTRACTOR_HPP

namespace MeowEngine::Rendering {
    struct  RenderExtractorInitData;
    struct RenderSceneData;
    struct RenderUIData;

    class IRenderExtractor {
    public:
        virtual ~IRenderExtractor() = default;
        virtual void Init(const RenderExtractorInitData& data) = 0;

        virtual void ExtractScene(RenderSceneData& data) = 0;
        virtual void ExtractUI(RenderUIData& data) = 0;

        virtual void Clear(RenderSceneData& sceneData, RenderUIData& uiData) = 0;
    };

}
#endif //MEOWENGINE_IRENDEREXTRACTOR_HPP
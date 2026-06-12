//
// Created by Akira Mujawar on 09/06/26.
//

#ifndef MEOWENGINE_RENDERUIEXTRACTOR_HPP
#define MEOWENGINE_RENDERUIEXTRACTOR_HPP

#include <Public/Threading/Forward.hpp>

#include <RenderUIData.hpp>
#include <RenderUIExtractorInitData.hpp>

namespace MeowEngine::Rendering {
    class RenderUIExtractor {
    public:
        RenderUIExtractor();
        ~RenderUIExtractor();

        void Init(const RenderUIExtractorInitData& data);
        void Schedule(Threading::Scheduler& scheduler);

        DoubleBuffer<RenderUIData>& GetRenderFrameData() {
            return RenderUIData;
        }

    private:
        void Clear();
        void Extract();

    private:
        DoubleBuffer<RenderUIData> RenderUIData;
        Runtime::GameplaySystem* Gameplay;
        Editor::Selector* Selector;
    };
}


#endif //MEOWENGINE_RENDERUIEXTRACTOR_HPP
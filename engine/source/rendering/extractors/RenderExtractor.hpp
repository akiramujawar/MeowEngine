//
// Created by Akira Mujawar on 12/06/26.
//

#ifndef MEOWENGINE_RENDEREXTRACTOR_HPP
#define MEOWENGINE_RENDEREXTRACTOR_HPP

#include <memory>

#include <Public/Threading/Forward.hpp>

#include <IRenderExtractor.hpp>
#include <RenderSceneData.hpp>
#include <RenderUIData.hpp>

namespace MeowEngine::Rendering {
    class RenderExtractorInitData;


    class RenderExtractor {
    public:
        RenderExtractor();
        ~RenderExtractor();

        void Init(const RenderExtractorInitData& data);
        void Schedule(Threading::Scheduler& scheduler);

        DoubleBuffer<RenderSceneData>& GetRenderSceneData() {
            return RenderSceneData;
        }

        DoubleBuffer<RenderUIData>& GetRenderUIData() {
            return RenderUIData;
        }

    private:
        DoubleBuffer<RenderUIData> RenderUIData;
        DoubleBuffer<RenderSceneData> RenderSceneData;

        std::unique_ptr<IRenderExtractor> Runtime;
        std::unique_ptr<IRenderExtractor> Editor;
    };
}

#endif //MEOWENGINE_RENDEREXTRACTOR_HPP
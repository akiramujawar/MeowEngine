//
// Created by Akira Mujawar on 17/05/26.
//

#ifndef MEOWENGINE_POSTPROCESSPASS_HPP
#define MEOWENGINE_POSTPROCESSPASS_HPP

#include <IRenderPass.hpp>

namespace MeowEngine::Rendering {
    class PostProcessPass : public IRenderPass {
    public:
        PostProcessPass();
        ~PostProcessPass() override;

        void Draw(RenderContext& context) override;
    };
}

#endif //MEOWENGINE_POSTPROCESSPASS_HPP
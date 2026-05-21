//
// Created by Akira Mujawar on 19/05/26.
//

#ifndef MEOWENGINE_SKYBOXPASS_HPP
#define MEOWENGINE_SKYBOXPASS_HPP

#include <IRenderPass.hpp>

namespace MeowEngine::Rendering {
    class SkyboxPass : public IRenderPass {
    public:
        SkyboxPass();
        ~SkyboxPass() override;

        void Draw(RenderContext& context) override;
    };
}

#endif //MEOWENGINE_SKYBOXPASS_HPP
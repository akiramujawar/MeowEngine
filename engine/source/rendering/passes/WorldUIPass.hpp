//
// Created by Akira Mujawar on 20/05/26.
//

#ifndef MEOWENGINE_WORLDUIPASS_HPP
#define MEOWENGINE_WORLDUIPASS_HPP

#include <IRenderPass.hpp>

namespace MeowEngine::Rendering {
    class WorldUIPass : public IRenderPass {
    public:
        WorldUIPass();
        ~WorldUIPass() override;

        void Draw(RenderContext& context) override;
    };
}

#endif //MEOWENGINE_WORLDUIPASS_HPP
//
// Created by Akira Mujawar on 19/05/26.
//

#ifndef MEOWENGINE_DEBUGPASS_HPP
#define MEOWENGINE_DEBUGPASS_HPP

#include <IRenderPass.hpp>

namespace MeowEngine::Rendering {
    class DebugPass : IRenderPass{
    public:
        DebugPass();
        ~DebugPass() override;

        void Draw(RenderContext& context) override;
    };
}

#endif //MEOWENGINE_DEBUGPASS_HPP
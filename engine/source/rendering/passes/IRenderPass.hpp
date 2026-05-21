//
// Created by Akira Mujawar on 20/05/26.
//

#ifndef MEOWENGINE_IRENDERPASS_HPP
#define MEOWENGINE_IRENDERPASS_HPP

namespace MeowEngine::Rendering {
    class RenderSceneData;
    struct RenderContext;

    class IRenderPass {
    public:
        virtual ~IRenderPass() = 0;
        virtual void Draw(RenderContext& context) = 0;
    };
}

#endif //MEOWENGINE_IRENDERPASS_HPP
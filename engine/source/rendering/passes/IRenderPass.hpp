//
// Created by Akira Mujawar on 20/05/26.
//

#ifndef MEOWENGINE_IRENDERPASS_HPP
#define MEOWENGINE_IRENDERPASS_HPP

namespace MeowEngine::Rendering {
    struct RenderSceneData;
    struct RenderContext;

    class IRenderPass {
    public:
        virtual ~IRenderPass() = default;
        virtual void Draw(RenderContext& context) = 0;
    };
}

#endif //MEOWENGINE_IRENDERPASS_HPP
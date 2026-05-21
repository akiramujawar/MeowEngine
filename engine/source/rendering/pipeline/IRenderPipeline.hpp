//
// Created by Akira Mujawar on 23/06/24.
//

#ifndef MEOWENGINE_IRENDERPIPELINE_HPP
#define MEOWENGINE_IRENDERPIPELINE_HPP

namespace MeowEngine::Rendering {
    class RenderContext;

    class IRenderPipeline {
    public:
        virtual ~IRenderPipeline() = default;
    };
}

#endif //MEOWENGINE_IRENDERPIPELINE_HPP

//
// Created by Akira Mujawar on 17/05/26.
//

#ifndef MEOWENGINE_GEOMETRYPASS_HPP
#define MEOWENGINE_GEOMETRYPASS_HPP

#include <IRenderPass.hpp>

namespace MeowEngine::Rendering {
    class GeometryPass : IRenderPass {
    public:
        GeometryPass();
        ~GeometryPass() override;

        void Draw(RenderContext& context) override;
    };
}

#endif //MEOWENGINE_GEOMETRYPASS_HPP
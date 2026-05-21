//
// Created by Akira Mujawar on 17/05/26.
//

#ifndef MEOWENGINE_GIZMOPASS_HPP
#define MEOWENGINE_GIZMOPASS_HPP

// ColliderPass.Begin()
//     Bind shader ONCE
//
//     Render all boxes
//     Render all spheres
//
// ColliderPass.End()

#include <IRenderPass.hpp>

namespace MeowEngine::Rendering {
    class GizmoPass : public IRenderPass {
    public:
        GizmoPass();
        ~GizmoPass() override;

        void Draw(RenderContext& context) override;
    };
}

#endif //MEOWENGINE_GIZMOPASS_HPP
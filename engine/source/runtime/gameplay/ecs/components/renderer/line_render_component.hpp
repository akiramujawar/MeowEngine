//
// Created by Akira Mujawar on 23/06/24.
//

#ifndef MEOWENGINE_LINE_RENDER_COMPONENT_HPP
#define MEOWENGINE_LINE_RENDER_COMPONENT_HPP

#include "RenderComponent.hpp"
#include "GLM_API.hpp"

// the grid will come in this
namespace MeowEngine::Runtime {
    class LineRenderComponent : public RenderComponent {
    public:
        REFLECT_COMPONENT(LineRenderComponent)
        static void Reflect();

        LineRenderComponent() = default;


//        void Update(const glm::mat4 &projectionViewMatrix) override {
////            MeshInstance->Update(projectionViewMatrix);
////            MeshInstance->RotateBy(0.1f);
//            ProjectionViewMatrix = projectionViewMatrix;
//        }

    public:
        glm::vec3 StartPoint;
        glm::vec3 EndPoint;
        glm::vec4 LineColor;
        std::vector<float> Vertices;
//        glm::mat4 ProjectionViewMatrix;
    };
}


#endif //MEOWENGINE_LINE_RENDER_COMPONENT_HPP

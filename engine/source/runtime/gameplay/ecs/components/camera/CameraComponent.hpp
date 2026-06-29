//
// Created by Akira Mujawar on 26/01/26.
//

#ifndef MEOWENGINE_CAMERA_COMPONENT_HPP
#define MEOWENGINE_CAMERA_COMPONENT_HPP

#include "IComponent.hpp"
#include "Transform3DComponent.hpp"
#include "Math.hpp"

namespace MeowEngine::Runtime {
    class CameraComponent : public Transform3DComponent {
    public:
        REFLECT_COMPONENT(CameraComponent)
        static void Reflect();

        CameraComponent() = default;
        ~CameraComponent() override = default;

        void UpdateMatrix();

        [[nodiscard]] Matrix4x4 GetProjection() const { return Projection;};
        [[nodiscard]] Matrix4x4 GetView() const { return View;};

        /**
         * Cached multiplication of project & view (to avoid unnecessary multiplications)
         * @return
         */
        [[nodiscard]] Matrix4x4 GetViewProjection () const { return ViewProjection;};

        void SetViewport(float width, float height);

    public:
        float MoveSpeed = 0.2f;
        float LookAroundSpeed = 0.15f;

    private:
        Matrix4x4 View {};
        Matrix4x4 Projection {};

        /**
         * cached multiplication of @View * @Projection
         */
        Matrix4x4 ViewProjection {};

        float Width = 100;
        float Height = 100;
        float Near = 0.1f;
        float Far = 3000;
    };
}


#endif //MEOWENGINE_CAMERA_COMPONENT_HPP

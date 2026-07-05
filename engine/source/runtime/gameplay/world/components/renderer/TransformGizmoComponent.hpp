//
// Created by Akira Mujawar on 18/02/26.
//

#ifndef MEOWENGINE_TRANSFORM_HANDLE_COMPONENT_HPP
#define MEOWENGINE_TRANSFORM_HANDLE_COMPONENT_HPP

#include "RenderComponent.hpp"

namespace MeowEngine::Runtime {
    class TransformGizmoComponent : public RenderComponent {
    public:
        REFLECT_COMPONENT(TransformGizmoComponent)
        static void Reflect();

        explicit TransformGizmoComponent();
        ~TransformGizmoComponent() override = default;
    };
}


#endif //MEOWENGINE_TRANSFORM_HANDLE_COMPONENT_HPP

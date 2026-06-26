//
// Created by Akira Mujawar on 18/02/26.
//

#ifndef MEOWENGINE_TRANSFORM_HANDLE_COMPONENT_HPP
#define MEOWENGINE_TRANSFORM_HANDLE_COMPONENT_HPP

#include "RenderComponent.hpp"

namespace MeowEngine::Runtime {
    class TransformHandleComponent : public MeowEngine::Runtime::RenderComponent {
    public:
        REFLECT_COMPONENT(TransformHandleComponent)
        static void Reflect();

        explicit TransformHandleComponent();
        ~TransformHandleComponent() override = default;
    };
}


#endif //MEOWENGINE_TRANSFORM_HANDLE_COMPONENT_HPP

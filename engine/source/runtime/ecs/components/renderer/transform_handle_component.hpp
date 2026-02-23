//
// Created by Akira Mujawar on 18/02/26.
//

#ifndef MEOWENGINE_TRANSFORM_HANDLE_COMPONENT_HPP
#define MEOWENGINE_TRANSFORM_HANDLE_COMPONENT_HPP

#include "render_component_base.hpp"

namespace MeowEngine::entity {
    class TransformHandleComponent : public MeowEngine::entity::RenderComponentBase {
    public:
        REFLECT_COMPONENT(TransformHandleComponent)
        static void Reflect();

        explicit TransformHandleComponent();
        explicit TransformHandleComponent(MeowEngine::assets::ShaderPipelineType shaderPipelineType);
        virtual ~TransformHandleComponent() = default;
    };
}


#endif //MEOWENGINE_TRANSFORM_HANDLE_COMPONENT_HPP

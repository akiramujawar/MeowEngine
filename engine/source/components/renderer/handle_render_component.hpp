//
// Created by Akira Mujawar on 18/02/26.
//

#ifndef MEOWENGINE_HANDLE_RENDER_COMPONENT_HPP
#define MEOWENGINE_HANDLE_RENDER_COMPONENT_HPP

#include "render_component_base.hpp"

namespace MeowEngine::entity {
    class HandleRenderComponent : public MeowEngine::entity::RenderComponentBase {
    public:
        REFLECT_COMPONENT(HandleRenderComponent)
        static void Reflect();

        explicit HandleRenderComponent();
        explicit HandleRenderComponent(MeowEngine::assets::ShaderPipelineType shaderPipelineType);
        virtual ~HandleRenderComponent() = default;
    };
}


#endif //MEOWENGINE_HANDLE_RENDER_COMPONENT_HPP

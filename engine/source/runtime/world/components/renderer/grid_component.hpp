//
// Created by Akira Mujawar on 19/02/26.
//

#ifndef MEOWENGINE_GRID_COMPONENT_HPP
#define MEOWENGINE_GRID_COMPONENT_HPP

#include "render_component_base.hpp"

namespace MeowEngine::component {
    class GridComponent : public entity::RenderComponentBase {
    public:
        REFLECT_COMPONENT(GridComponent)
        static void Reflect();

        explicit GridComponent();
        explicit GridComponent(MeowEngine::assets::ShaderPipelineType shaderPipelineType);
        virtual ~GridComponent() = default;
    };
}

#endif //MEOWENGINE_GRID_COMPONENT_HPP

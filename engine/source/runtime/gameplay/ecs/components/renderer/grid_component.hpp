//
// Created by Akira Mujawar on 19/02/26.
//

#ifndef MEOWENGINE_GRID_COMPONENT_HPP
#define MEOWENGINE_GRID_COMPONENT_HPP

#include "render_component_base.hpp"
#include "AssetHandle.hpp"

namespace MeowEngine::Runtime {
    class GridComponent : public Runtime::RenderComponentBase {
    public:
        REFLECT_COMPONENT(GridComponent)
        static void Reflect();

        explicit GridComponent();
        explicit GridComponent(MeowEngine::assets::ShaderPipelineType shaderPipelineType);
        virtual ~GridComponent() = default;

    private:
        Asset::AssetHandle FragmentShader;
        Asset::AssetHandle VertexShader;
    };
}

#endif //MEOWENGINE_GRID_COMPONENT_HPP

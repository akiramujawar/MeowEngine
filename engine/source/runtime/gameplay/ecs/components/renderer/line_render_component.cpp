//
// Created by Akira Mujawar on 23/06/24.
//

#include "line_render_component.hpp"
#include <log.hpp>

namespace MeowEngine::Runtime {
    using Asset::AssetHandle;

    void LineRenderComponent::Reflect() {
        REGISTER_PROPERTY(LineRenderComponent, ShaderHandle, AssetHandle, true, false);
    }

    // LineRenderComponent::LineRenderComponent(MeowEngine::assets::ShaderPipelineType shader, glm::vec3 start, glm::vec3 end) {
    //     Shader = shader;
    //     StartPoint = start;
    //     EndPoint = end;
    //     LineColor = glm::vec4(0.4f,1,1,0.3f);
    //
    //     Vertices = {
    //         start.x, start.y, start.z,
    //         end.x, end.y, end.z,
    //     };
    // }

}
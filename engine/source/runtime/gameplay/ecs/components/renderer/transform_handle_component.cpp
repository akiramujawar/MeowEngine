//
// Created by Akira Mujawar on 18/02/26.
//

#include "transform_handle_component.hpp"

namespace MeowEngine::Runtime {
    using Asset::AssetHandle;

    void TransformHandleComponent::Reflect() {
        REGISTER_PROPERTY(TransformHandleComponent, ShaderHandle, AssetHandle, true, false);
    }

    TransformHandleComponent::TransformHandleComponent() {}

}
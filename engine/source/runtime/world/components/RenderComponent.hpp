//
// Created by Akira Mujawar on 23/06/24.
//

#ifndef MEOWENGINE_RENDER_COMPONENT_HPP
#define MEOWENGINE_RENDER_COMPONENT_HPP

#include "IComponent.hpp"
#include "AssetHandle.hpp"

namespace MeowEngine::Runtime {
    /**
     * This class is extended for mesh, debug & ui rendering
     */
    class RenderComponent : public IComponent {
    protected:
        RenderComponent() = default;
        ~RenderComponent() override = default;

    public:
        [[nodiscard]] Asset::AssetHandle GetShaderAssetHandle() const { return ShaderAssetHandle; }

    protected:
        Asset::AssetHandle ShaderAssetHandle;
    };
}

#endif //MEOWENGINE_RENDER_COMPONENT_HPP

//
// Created by Akira Mujawar on 23/06/24.
//

#ifndef MEOWENGINE_MESH_RENDER_COMPONENT_HPP
#define MEOWENGINE_MESH_RENDER_COMPONENT_HPP

#include "RenderComponent.hpp"

namespace MeowEngine::Runtime {
    class MeshRenderComponent : public RenderComponent {

    public:
        REFLECT_COMPONENT(MeshRenderComponent)
        static void Reflect();

        explicit MeshRenderComponent() = default;
        ~MeshRenderComponent() override = default;

        [[nodiscard]] const Asset::AssetHandle& GetMeshAssetHandle() const { return MeshAssetHandle; }
        [[nodiscard]] const Asset::AssetHandle& GetTextureAssetHandle() const { return TextureAssetHandle; }

    private:
        // MeowEngine::StaticMeshInstance* MeshInstance;
        Asset::AssetHandle MeshAssetHandle;
        Asset::AssetHandle TextureAssetHandle;
    };
}


#endif //MEOWENGINE_MESH_RENDER_COMPONENT_HPP

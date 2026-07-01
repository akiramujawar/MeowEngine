//
// Created by Akira Mujawar on 23/06/24.
//

#ifndef MEOWENGINE_MESH_RENDER_COMPONENT_HPP
#define MEOWENGINE_MESH_RENDER_COMPONENT_HPP

#include "RenderComponent.hpp"
#include "static_mesh_instance.hpp"

namespace MeowEngine::Runtime {
    class MeshRenderComponent : public RenderComponent {

    public:
        REFLECT_COMPONENT(MeshRenderComponent)
        static void Reflect();

        explicit MeshRenderComponent() = default;
        ~MeshRenderComponent() override = default;
        // explicit MeshRenderComponent(MeowEngine::assets::ShaderPipelineType shader, MeowEngine::StaticMeshInstance* meshInstance);

//        void Update(const glm::mat4 &projectionViewMatrix) override {
//            MeshInstance->Update(projectionViewMatrix);
//            MeshInstance->RotateBy(0.1f);
//        }

        // const MeowEngine::StaticMeshInstance& GetMeshInstance() const {
        //     return *MeshInstance;
        // }

        const Asset::AssetHandle& GetMeshAssetHandle() const { return MeshAssetHandle; }
        const Asset::AssetHandle& GetTextureAssetHandle() const { return TextureAssetHandle; }

    private:
        // MeowEngine::StaticMeshInstance* MeshInstance;
        Asset::AssetHandle MeshAssetHandle;
        Asset::AssetHandle TextureAssetHandle;
    };
}


#endif //MEOWENGINE_MESH_RENDER_COMPONENT_HPP

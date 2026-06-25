//
// Created by Akira Mujawar on 18/05/26.
//

#include <RenderResourceManager.hpp>

namespace MeowEngine::Rendering {
    RenderResourceManager::RenderResourceManager() = default;
    RenderResourceManager::~RenderResourceManager() = default;

    // ShaderRenderHandle RenderResourceManager::ResolveShaderHandle(Asset::AssetHandle vertex, Asset::AssetHandle fragment) {
    //     ShaderRenderHandle handle {};
    //
    //     auto test = ShaderResources.find(handle);
    // }
    //
    // MeshRenderHandle RenderResourceManager::ResolveMeshHandle(Asset::AssetHandle mesh) {
    //
    // }
    //
    // TextureRenderHandle RenderResourceManager::ResolveTextureHandle(Asset::AssetHandle bitmap) {}

    GLShaderResource& RenderResourceManager::GetShaderResource(ShaderRenderHandle asset) {
        auto [iterator, inserted] = ShaderResources.try_emplace(asset, asset.AssetHandle);

        return iterator->second;
    }

    GLMeshResource& RenderResourceManager::GetMeshResource(MeshRenderHandle asset) {
        auto [iterator, inserted] = MeshResources.try_emplace(asset, asset.MeshAsset);

        return iterator->second;
    }

    GLTextureResource& RenderResourceManager::GetTextureResource(TextureRenderHandle asset) {
        auto [iterator, inserted] = TextureResources.try_emplace(asset, asset.BitmapAsset);

        return iterator->second;
    }
}

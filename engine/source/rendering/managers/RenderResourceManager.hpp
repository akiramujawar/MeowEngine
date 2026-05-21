//
// Created by Akira Mujawar on 18/05/26.
//

#ifndef MEOWENGINE_RENDERRESOURCEMANAGER_HPP
#define MEOWENGINE_RENDERRESOURCEMANAGER_HPP

#include <unordered_map>

#include <ShaderRenderHandle.hpp>
#include <MeshRenderHandle.hpp>
#include <TextureRenderHandle.hpp>

#include <GLShaderResource.hpp>
#include <GLMeshResource.hpp>
#include <GLTextureResource.hpp>

namespace MeowEngine::Rendering {
    /**
     * TODO: in extraction we resolve AssetHandle to ResourceHandle
     * TODO: because asset handle needs to load from disk where as a resource handle is created in runtime
     * TODO: in multi threading this the loading from disk goes to main thread and not render thread
     */
    class RenderResourceManager {
    public:
        RenderResourceManager();
        ~RenderResourceManager();

        // ShaderRenderHandle ResolveShaderHandle(Asset::AssetHandle vertex, Asset::AssetHandle fragment);
        // MeshRenderHandle ResolveMeshHandle(Asset::AssetHandle mesh);
        // TextureRenderHandle ResolveTextureHandle(Asset::AssetHandle bitmap);

        GLShaderResource& GetShaderResource(ShaderRenderHandle asset);
        GLMeshResource& GetMeshResource(MeshRenderHandle asset);
        GLTextureResource& GetTextureResource(TextureRenderHandle asset);

    private:
        std::unordered_map<ShaderRenderHandle, GLShaderResource> ShaderResources;
        std::unordered_map<MeshRenderHandle, GLMeshResource> MeshResources;
        std::unordered_map<TextureRenderHandle, GLTextureResource> TextureResources;
    };
}


#endif //MEOWENGINE_RENDERRESOURCEMANAGER_HPP
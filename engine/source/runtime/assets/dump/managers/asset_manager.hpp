//
// Created by Akira Mujawar on 21/06/24.
//

#ifndef MEOWENGINE_ASSET_MANAGER_HPP
#define MEOWENGINE_ASSET_MANAGER_HPP

#include "asset_inventory.hpp"
#include "vector"

namespace MeowEngine {
    struct AssetManager {
        virtual void LoadShaderPipelines(const std::vector<MeowEngine::assets::ShaderPipelineType>& shaderPipelines) = 0;
        virtual void LoadStaticMeshes(const std::vector<MeowEngine::assets::StaticMeshType>& staticMeshes) = 0;
        virtual void LoadTextures(const std::vector<MeowEngine::assets::TextureType>& textures) = 0;

        // template<typename T>
        // static T* Load(const std::string& path);
        //
        // static void Unload(AssetHandle handle);
        // static AssetHandle Import(const std::string& file);

        // getasset<type>
    };
}


#endif //MEOWENGINE_ASSET_MANAGER_HPP

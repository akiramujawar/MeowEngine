//
// Created by Akira Mujawar on 25/06/26.
//

#include "AssetBuilder.hpp"


#include "ShaderBuilder.hpp"


namespace MeowEngine::Asset {
    void AssetBuilder::Build() {
        // get path to engine shader folder
        // put the cache in root .cache
        // get path to sandbox shader folder
        // put the cache in root .cache
        // link in cmake as

        ShaderBuilder::CreateShaderAssets();
    }
}
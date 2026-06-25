//
// Created by Akira Mujawar on 25/06/26.
//

#include "AssetBuilder.hpp"


#include "ShaderBuilder.hpp"


namespace MeowEngine::Asset {
    void AssetBuilder::Build() {
        ShaderBuilder::CreateShaderAssets();
    }
}
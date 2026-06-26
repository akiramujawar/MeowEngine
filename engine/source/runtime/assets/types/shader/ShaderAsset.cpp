//
// Created by Akira Mujawar on 25/06/26.
//

#include "ShaderAsset.hpp"

namespace MeowEngine::Asset {

    void ShaderAsset::SetSource(ShaderType type, const std::string& source) {
        switch (type) {
            case ShaderType::VERTEX:
                VertexSource = source;
                break;
            case ShaderType::FRAGMENT:
                FragmentSource = source;
                break;
            case ShaderType::INVALID:
                break;
            case ShaderType::SHADER_COUNT:
                break;
        }
    }

}
//
// Created by Akira Mujawar on 25/06/26.
//

#ifndef MEOWENGINE_SHADERTYPE_HPP
#define MEOWENGINE_SHADERTYPE_HPP

namespace MeowEngine::Asset {
    enum class ShaderType : int {
        INVALID = -1,
        VERTEX,
        FRAGMENT,
        SHADER_COUNT
    };
}

#endif //MEOWENGINE_SHADERTYPE_HPP
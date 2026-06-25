//
// Created by Akira Mujawar on 25/06/26.
//

#ifndef MEOWENGINE_SHADERIMPORTER_HPP
#define MEOWENGINE_SHADERIMPORTER_HPP

#include "Public/Core/Forward.hpp"

namespace MeowEngine::Asset {
    class ShaderImporter {
    public:
        static void Import(const Path& exportPath, const Path& vertexPath, const Path& fragmentPath);
    };
}


#endif //MEOWENGINE_SHADERIMPORTER_HPP
//
// Created by Akira Mujawar on 01/07/26.
//

#ifndef MEOWENGINE_MESHSERIALIZER_HPP
#define MEOWENGINE_MESHSERIALIZER_HPP

#include "Public/Core/Forward.hpp"
#include "mesh.hpp"

namespace MeowEngine::Asset {
    class MeshSerializer {
    public:
        static bool Serialize(const Path& path, const std::string& data);
        static bool Deserialize(const Path& path, Mesh& asset);
    };
}


#endif //MEOWENGINE_MESHSERIALIZER_HPP
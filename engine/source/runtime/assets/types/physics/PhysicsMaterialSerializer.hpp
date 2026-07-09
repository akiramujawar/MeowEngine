//
// Created by Akira Mujawar on 09/07/26.
//

#ifndef MEOWENGINE_PHYSICSMATERIALSERIALIZER_HPP
#define MEOWENGINE_PHYSICSMATERIALSERIALIZER_HPP

#include "Public/Core/Forward.hpp"

#include "PhysicsMaterialAsset.hpp"

namespace MeowEngine::Asset {
    class PhysicsMaterialSerializer {
    public:
        static bool Serialize(const Path& path, PhysicsMaterialAsset& asset);
        static bool Deserialize(const Path& path, PhysicsMaterialAsset& asset);
    };
}


#endif //MEOWENGINE_PHYSICSMATERIALSERIALIZER_HPP
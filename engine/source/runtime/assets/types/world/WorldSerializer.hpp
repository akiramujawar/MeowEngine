//
// Created by Akira Mujawar on 11/03/26.
//

#ifndef MEOWENGINE_WORLDSERIALIZER_HPP
#define MEOWENGINE_WORLDSERIALIZER_HPP

#include "Public/Core/Forward.hpp"
#include "World.hpp"

namespace MeowEngine::Asset {


    class WorldSerializer {
    public:
        static bool Serialize(const Path& path, World& world);
        static bool Deserialize(const Path& path, World& world);
    };
}


#endif //MEOWENGINE_WORLDSERIALIZER_HPP
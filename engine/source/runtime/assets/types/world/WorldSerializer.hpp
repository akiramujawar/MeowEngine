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
        static bool Serialize(Path path, Runtime::World& world);
        static bool Deserialize(Path path, Runtime::World& world);
    };
}


#endif //MEOWENGINE_WORLDSERIALIZER_HPP
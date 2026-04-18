//
// Created by Akira Mujawar on 11/03/26.
//

#ifndef MEOWENGINE_WORLDSERIALIZER_HPP
#define MEOWENGINE_WORLDSERIALIZER_HPP

// #include <IO.hpp>
#include <../main/core/World.hpp>

namespace MeowEngine::Core::IO::FileSystem {
    class Path;
}

namespace MeowEngine::Runtime {
    namespace FileSystem = Core::IO::FileSystem;

    class WorldSerializer {
    public:
        static void Serialize(const FileSystem::Path path, World& world);

        static void Deserialize(const FileSystem::Path path, World& world);
    };
}


#endif //MEOWENGINE_WORLDSERIALIZER_HPP
//
// Created by Akira Mujawar on 11/03/26.
//

#ifndef MEOWENGINETEST2_WORLDSERIALIZER_HPP
#define MEOWENGINETEST2_WORLDSERIALIZER_HPP

#include <IO.hpp>
#include <World.hpp>


namespace MeowEngine::Runtime {
    class WorldSerializer {
    public:
        void Serialize(const FileSystem::Path path, const World& world) {

        }

        void Deserialize(const FileSystem::Path path, World& world);
    };
}


#endif //MEOWENGINETEST2_WORLDSERIALIZER_HPP
//
// Created by Akira Mujawar on 16/05/26.
//

#include <WorldCreator.hpp>

#include <WorldSerializer.hpp>
#include <DefaultWorld.hpp>

namespace MeowEngine::Editor {
    void WorldCreator::CreateDefault(std::string path) {
        Runtime::World* world = new DefaultWorld();
        // Runtime::WorldSerializer::Serialize("", *world);
    }
}

//
// Created by Akira Mujawar on 22/06/26.
//

#ifndef MEOWENGINE_REFLECTIONWORLD_HPP
#define MEOWENGINE_REFLECTIONWORLD_HPP

#include <World.hpp>

namespace MeowEngine::Runtime {
    class ReflectionWorld : public Asset::World {
    public:
        ReflectionWorld();
        ~ReflectionWorld();

    private:
        void CreateCamera();
        void CreateEmtpy(std::string name);
        void CreateReflectionTest();
    };
}


#endif //MEOWENGINE_REFLECTIONWORLD_HPP
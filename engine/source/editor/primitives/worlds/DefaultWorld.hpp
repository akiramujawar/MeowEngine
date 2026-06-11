//
// Created by Akira Mujawar on 16/05/26.
//

#ifndef MEOWENGINE_DEFAULTWORLD_HPP
#define MEOWENGINE_DEFAULTWORLD_HPP

#include <World.hpp>

namespace MeowEngine::Editor {
    class DefaultWorld : public Runtime::World {
    public:
        DefaultWorld();
        ~DefaultWorld();
    private:
        void CreateCamera();
        void CreateGrid();
        void CreateSky();
        void CreateTransformHandle();

        void CreateHierarchyTest();
        void CreateReflectionTest();

        void CreateEmptyLine();
        entt::entity CreateDefaultEntity(std::string name);
    };
}


#endif //MEOWENGINE_DEFAULTWORLD_HPP
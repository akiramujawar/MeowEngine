//
// Created by Akira Mujawar on 25/06/26.
//

#ifndef MEOWENGINE_HIERARCHYWORLD_HPP
#define MEOWENGINE_HIERARCHYWORLD_HPP


#include <World.hpp>

namespace MeowEngine::Runtime {
    class HierarchyWorld : public Asset::World {
    public:
        HierarchyWorld();
        ~HierarchyWorld() = default;

    private:
        void CreateCamera();
        void CreateHierarchy();
        EntityHandle CreateDefaultEntity(std::string name);

    };
}


#endif //MEOWENGINE_HIERARCHYWORLD_HPP
//
// Created by Akira Mujawar on 26/06/26.
//

#ifndef MEOWENGINE_ICOMPONENTSYSTEM_HPP
#define MEOWENGINE_ICOMPONENTSYSTEM_HPP

namespace MeowEngine::Asset {
    class World;
}

namespace MeowEngine::Runtime {
    class IComponentSystem {
    public:
        virtual ~IComponentSystem() = default;

        virtual void Update(Asset::World& world) = 0;
    };
}

#endif //MEOWENGINE_ICOMPONENTSYSTEM_HPP
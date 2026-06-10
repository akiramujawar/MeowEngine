//
// Created by Akira Mujawar on 17/04/26.
//

#ifndef MEOWENGINE_GAMEPLAYSYSTEM_HPP
#define MEOWENGINE_GAMEPLAYSYSTEM_HPP

#include <World.hpp>
// #include <atomic>

namespace MeowEngine::Runtime {
    /**
     * Reads physics snapshot from physics system & applies to World
     * Prepares render & physics snapshot (to be utilised by respective systems)
     * Emits commands if required for physics / render systems
     */
    class GameplaySystem {
    public:
        GameplaySystem();
        ~GameplaySystem();

        void SetWorld(World* world);
        World& GetWorld();

        void Input();
        void Update();
        void Sync();

    private:
        World* World;
    };

}


#endif //MEOWENGINE_GAMEPLAYSYSTEM_HPP
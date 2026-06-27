//
// Created by Akira Mujawar on 17/04/26.
//

#ifndef MEOWENGINE_GAMEPLAYSYSTEM_HPP
#define MEOWENGINE_GAMEPLAYSYSTEM_HPP

#include <memory>
#include <vector>

#include "IComponent.hpp"
#include "World.hpp"
#include "IComponentSystem.hpp"
#include "Math.hpp"

namespace MeowEngine::Runtime {
    class PerspectiveCameraComponent;

    /**
     * Reads physics snapshot from physics system & applies to World
     * Prepares render & physics snapshot (to be utilised by respective systems)
     * Emits commands if required for physics / render systems
     */
    class GameplaySystem {
    public:
        GameplaySystem();
        ~GameplaySystem();

        void SetWorld(Asset::World* world);

        Asset::World& GetWorld();


        void Input();
        void Update();
        void Sync();

        void SetViewport(const float& width, const float& height);
        PerspectiveCameraComponent& GetCamera() const;

    private:
        Asset::World* World;
        std::vector<std::unique_ptr<Runtime::IComponentSystem>> ComponentSystems;
    };

}


#endif //MEOWENGINE_GAMEPLAYSYSTEM_HPP
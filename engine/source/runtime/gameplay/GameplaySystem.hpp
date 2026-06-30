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
    class CameraComponent;

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

        void StartSimulation();
        void PauseSimulation();
        void UnpauseSimulation();
        void StopSimulation();

        void Input();
        void Update() const;

        void SetViewport(const float& width, const float& height);
        void ResetCamera() const;

        [[nodiscard]] CameraComponent& GetCamera() const;
        [[nodiscard]] bool GetIsSimulating() const { return IsSimulating; };
        [[nodiscard]] bool GetIsPaused() const { return IsPaused; };

    private:
        Asset::World* World;

        /**
         * Systems which are persistent and never stop
         * e.g. CameraSystem, TransformSystem
         */
        std::vector<std::unique_ptr<IComponentSystem>> CommonSystems;

        /**
         * Systems which only run when engine is simulating the world
         * e.g. PlayerSystem & user added systems
         */
        std::vector<std::unique_ptr<IComponentSystem>> SimulationSystems;

        float Width;
        float Height;
        bool IsSimulating;
        bool IsPaused;
    };

}


#endif //MEOWENGINE_GAMEPLAYSYSTEM_HPP
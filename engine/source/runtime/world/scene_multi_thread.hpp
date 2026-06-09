//
// Created by Akira Mujawar on 21/06/24.
//

#ifndef MEOWENGINE_MAIN_SCENE_HPP
#define MEOWENGINE_MAIN_SCENE_HPP

#include "internal_ptr.hpp"

#include "asset_manager.hpp"
#include "InputManager.hpp"
#include <opengl_render_system.hpp>
#include "PhysicsSystem.hpp"

#include "Public/Math.hpp"

namespace MeowEngine {
    struct SceneMultiThread {
        SceneMultiThread(const Vector2Int& frameSize);

        void OnWindowResized(const Vector2Int& size);
        void Save();

        // -----------------------------------------------------------------------

        virtual void LoadOnRenderSystem(std::shared_ptr<MeowEngine::AssetManager> assetManager);

        /**
         * Creates scenes, adds entity / components
         * (essentially later this might be a done dynamically by reading a saved scene data)
         */
        void CreateSceneOnMainSystem();

        bool AddRemoveEntitiesOnMainThread();

        /**
        * When a entity is created on main thread, out buffer queues the entity to be created on physics thread
        * and adds to staging(physics) buffer
        * @param inPhysics
        */
        bool AddEntitiesOnPhysicsSystem(MeowEngine::Physics::PhysicsSystem* inPhysics);

        // -----------------------------
        void Input(const float &deltaTime, const MeowEngine::Input::InputManager& inputManager);

        // -----------------------------
        virtual void Update(const float& deltaTime);

        // -----------------------------
        void RenderGameView(MeowEngine::OpenGLRenderSystem& renderer);
        void RenderUserInterface(MeowEngine::OpenGLRenderSystem& renderer, unsigned int frameBufferId, const double fps);

        // -----------------------------

        /**
         * Simply swap the entt registry current(main) and final(render)
         */
        void SwapMainAndRenderBufferOnMainSystem();

        // -----------------------------

        /**
         * Based on availability of staging(physics) buffer  we either
         * cache or sync data from main & render to physics & vice versa
         * i.e. we take the updates from physics thread and push the updates from main thread w.r.t render thread
         * @param inIsPhysicsThreadWorking
         */
        void SyncPhysicsBufferOnMainSystem(bool inIsPhysicsThreadWorking);

        /**
         * Sync UI updates and push main thread updates on final(render) buffer
         * and create queue for physics thread for UI updates
         */
        void SyncRenderBufferOnMainThread();

        /**
         * Push rigidbody updates to transform & apply UI inputs to staging(physics) buffer
         */
        void SyncPhysicsBufferOnPhysicsSystem(MeowEngine::Physics::PhysicsSystem* inPhysics);

        // -----------------------------


    private:
        struct Internal;
        MeowEngine::internal_ptr<Internal> InternalPointer;
    };
}


#endif //MEOWENGINE_SCENE_MULTI_THREAD_HPP

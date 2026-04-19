//
// Created by Akira Mujawar on 21/06/24.
//

#ifndef MEOWENGINE_RENDER_SYSTEM_HPP
#define MEOWENGINE_RENDER_SYSTEM_HPP

#pragma once

#include "entt.hpp"
#include "perspective_camera.hpp"
#include "selection_data.hpp"
#include "reflection_property_change.hpp"
#include "queue"

namespace MeowEngine::Runtime::Systems {
    /**
     * Reads & Renders render snapshot from main system
     * Emits events like input, debug, ui interactions
     */
    struct RenderSystem {
    private:
        void Render();

    public:
        virtual void RenderGameView(MeowEngine::PerspectiveCamera* cameraObject,
                                    entt::registry& registry,
                                    MeowEngine::SelectionData& pSelection) {};

        virtual void RenderUserInterface(entt::registry& registry,
                                         std::queue<std::shared_ptr<MeowEngine::ReflectionPropertyChange>>& inUIInputQueue,
                                         MeowEngine::SelectionData& pSelection,
                                         unsigned int frameBufferId,
                                         const double fps) {};

        virtual void RenderPhysics(MeowEngine::PerspectiveCamera* cameraObject, entt::registry& registry) {};
    };
}


#endif //MEOWENGINE_RENDER_SYSTEM_HPP

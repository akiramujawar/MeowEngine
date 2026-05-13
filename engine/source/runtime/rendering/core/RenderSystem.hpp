//
// Created by Akira Mujawar on 21/06/24.
//

#ifndef MEOWENGINE_RENDER_SYSTEM_HPP
#define MEOWENGINE_RENDER_SYSTEM_HPP

#pragma once

// TODO: make it abstract
#include <SDL_EngineWindow.hpp>
#include <opengl_framebuffer.hpp>

namespace MeowEngine::Shared {
    class RenderGraph;
}


namespace MeowEngine::Runtime::Systems {
    /**
     * Reads & Renders render snapshot from main system
     * Emits events like input, debug, ui interactions
     */
    struct RenderSystem {
        explicit RenderSystem(Shared::RenderGraph&);
        ~RenderSystem();

    private:
        void Render();

    private:
        /*
         * TODO: When we plan to handle multi-scene we look into this, make this private
         * we decouple window / context into a class
         */
        SDL_EngineWindow Window;

        /**
         * Draws our game view onto a ui panel (which is a framebuffer)
         */
        OpenGLFrameBuffer FrameBuffer;

        /**
         * Accesses various render passes and draws them
         */
        Shared::RenderGraph& Graph;
    };
}

#endif //MEOWENGINE_RENDER_SYSTEM_HPP

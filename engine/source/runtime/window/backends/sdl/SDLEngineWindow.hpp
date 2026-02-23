//
// Created by Akira Mujawar on 22/10/24.
//

#ifndef MEOWENGINE_WINDOW_HPP
#define MEOWENGINE_WINDOW_HPP

#include "SDLAPI.hpp"

#include "Vector2Uint.hpp"
#include "log.hpp"

namespace MeowEngine {
    struct SDLEngineWindow {
        SDLEngineWindow();
        ~SDLEngineWindow();

        void SwapWindow() const;
        MeowEngine::WindowSize GetWindowSize();
        void ClearContext() const;
        void MakeCurrent() const;

        SDL_Window* GetWindow() const;
        SDL_GLContext GetContext() const;

    private:
        SDL_Window* CreateWindow(const uint32_t& windowFlags);
        SDL_GLContext CreateContext();

        bool ShouldDisplayFullScreen();
        MeowEngine::WindowSize GetInitialWindowSize();

    private:
        SDL_Window* window;
        SDL_GLContext context;
    };
}


#endif //MEOWENGINE_WINDOW_HPP

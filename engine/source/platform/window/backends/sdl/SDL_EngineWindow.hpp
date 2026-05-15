//
// Created by Akira Mujawar on 22/10/24.
//

#ifndef MEOWENGINE_WINDOW_HPP
#define MEOWENGINE_WINDOW_HPP

#include <SDL_API.hpp>

#include <Public/Math.hpp>
#include <log.hpp>

namespace MeowEngine::Platform {
    /**
     * TODO: Decouple sdl and opengl
     */
    struct SDL_EngineWindow {
        SDL_EngineWindow();
        ~SDL_EngineWindow();

        void SwapWindow() const;
        Vector2Int GetWindowSize();
        void ClearContext() const;
        void MakeCurrent() const;

        [[nodiscard]] SDL_Window* GetHandle() const;
        [[nodiscard]] SDL_GLContext GetContext() const;

    private:
        SDL_Window* CreateHandle(const uint32_t& windowFlags);
        SDL_GLContext CreateContext();

        bool ShouldDisplayFullScreen();
        Vector2Int GetInitialWindowSize();

    private:
        SDL_Window* Handle;
        SDL_GLContext Context;
    };
}


#endif //MEOWENGINE_WINDOW_HPP

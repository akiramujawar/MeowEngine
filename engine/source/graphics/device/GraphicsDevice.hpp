//
// Created by Akira Mujawar on 23/02/26.
//

#ifndef MEOWENGINE_IRENDERDEVICE_HPP
#define MEOWENGINE_IRENDERDEVICE_HPP

// TODO: make it abstract
#include <SDL_EngineWindow.hpp>

namespace MeowEngine::Graphics {
    class GraphicsDevice {
    public:
        GraphicsDevice();
        ~GraphicsDevice();

        [[nodiscard]] Platform::SDL_EngineWindow& GetWindow();

    private:
        /*
         * TODO: When we plan to handle multi-scene we look into this, make this private
         * we decouple window / context into a class
         */
        Platform::SDL_EngineWindow Window;
    };
}


#endif //MEOWENGINE_IRENDERDEVICE_HPP

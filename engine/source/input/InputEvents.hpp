//
// Created by Akira Mujawar on 09/06/26.
//

#ifndef MEOWENGINE_INPUTEVENTS_HPP
#define MEOWENGINE_INPUTEVENTS_HPP

// TODO: check on removing this for optimisation
#include <SDL_API.hpp>
#include <vector>

namespace MeowEngine::Input {
    typedef std::vector<SDL_Event> InputEvents;
    typedef const uint8_t* KeyboardState;
    typedef uint32_t MouseState;
}

#endif //MEOWENGINE_INPUTEVENTS_HPP
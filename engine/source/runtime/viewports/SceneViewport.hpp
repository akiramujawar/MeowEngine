//
// Created by Akira Mujawar on 29/06/26.
//

#ifndef MEOWENGINE_SCENEVIEWPORT_HPP
#define MEOWENGINE_SCENEVIEWPORT_HPP

// NOTE: not implemented
namespace MeowEngine::Runtime {
    struct Viewport {
        int Width;
        int Height;
        // render target
    };

    // runtime manager
    // on render thread
    // on load/create the renderer panels send a command with guid, and viewport size
    // creates a required frame buffer and stores in gpu resource

    // on main thread
    // on command
    // creates a render target handle with uuid passed by command
    // creates required handle & stores viewport data
    
}

#endif //MEOWENGINE_SCENEVIEWPORT_HPP
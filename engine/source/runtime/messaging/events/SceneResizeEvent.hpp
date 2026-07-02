//
// Created by Akira Mujawar on 02/07/26.
//

#ifndef MEOWENGINE_SCENERESIZEEVENT_HPP
#define MEOWENGINE_SCENERESIZEEVENT_HPP

namespace MeowEngine::Messaging {
    struct SceneViewportResizeEvent {
        float Width;
        float Height;
    };
}

#endif //MEOWENGINE_SCENERESIZEEVENT_HPP
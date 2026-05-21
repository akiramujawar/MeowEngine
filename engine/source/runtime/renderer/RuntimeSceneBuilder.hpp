//
// Created by Akira Mujawar on 21/06/24.
//

#ifndef MEOWENGINE_RUNTIMESCENEBUILDER_HPP
#define MEOWENGINE_RUNTIMESCENEBUILDER_HPP

#pragma once

namespace MeowEngine::Rendering {
    class RenderGraph;
}

namespace MeowEngine::Runtime {
    /**
     * decide setup required for set pass calls
     */
    struct RuntimeSceneBuilder {
        explicit RuntimeSceneBuilder();
        ~RuntimeSceneBuilder();

        void Init();

        // bool ShowGizmos;
    };
}

#endif //MEOWENGINE_RUNTIMESCENEBUILDER_HPP

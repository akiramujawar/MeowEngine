//
// Created by Akira Mujawar on 21/06/24.
//

#ifndef MEOWENGINE_RENDER_SYSTEM_HPP
#define MEOWENGINE_RENDER_SYSTEM_HPP

#pragma once

namespace MeowEngine::Rendering {
    class RenderGraph;
}

namespace MeowEngine::Runtime {
    /**
     * Reads & Renders render snapshot from main system
     * Emits events like input, debug, ui interactions
     * Handles the rendering order
     */
    struct RuntimeWorldBuilder {
        explicit RuntimeWorldBuilder();
        ~RuntimeWorldBuilder();

        void Init();
        void BuildGraph(Rendering::RenderGraph& graph);
    };
}

#endif //MEOWENGINE_RENDER_SYSTEM_HPP

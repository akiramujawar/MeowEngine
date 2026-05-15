//
// Created by Akira Mujawar on 22/02/26.
//

#ifndef MEOWENGINE_IEDITORUISYSTEM_HPP
#define MEOWENGINE_IEDITORUISYSTEM_HPP

#include <ImguiEditorUISystem.hpp>

namespace MeowEngine::Graphics {
    class GraphicsDevice;
}

namespace MeowEngine::Rendering {
    class RenderGraph;
}

namespace MeowEngine::Editor {
    /**
     * Handles editor specific rendering like editor ui, gizmos and rendering order
     */
    class RenderPipeline {
    public:
        explicit RenderPipeline(Graphics::GraphicsDevice& device);
        ~RenderPipeline();

        void BuildGraph(Rendering::RenderGraph& graph);

    private:
        ImGuiEditorUISystem UI;
    };
}


#endif //MEOWENGINE_IEDITORUISYSTEM_HPP

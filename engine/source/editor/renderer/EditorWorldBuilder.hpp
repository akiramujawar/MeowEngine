//
// Created by Akira Mujawar on 22/02/26.
//

#ifndef MEOWENGINE_IEDITORUISYSTEM_HPP
#define MEOWENGINE_IEDITORUISYSTEM_HPP

namespace MeowEngine::Rendering {
    class RenderGraph;
}

namespace MeowEngine::Editor {
    /**
     * Handles editor specific rendering like editor ui, gizmos and rendering order
     */
    class EditorWorldBuilder {
    public:
        EditorWorldBuilder();
        ~EditorWorldBuilder();

        void Init();
        void BuildGraph(Rendering::RenderGraph& graph);

    private:
    };
}


#endif //MEOWENGINE_IEDITORUISYSTEM_HPP

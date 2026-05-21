//
// Created by Akira Mujawar on 22/02/26.
//

#ifndef MEOWENGINE_EDITORSCENEBUILDER_HPP
#define MEOWENGINE_EDITORSCENEBUILDER_HPP

namespace MeowEngine::Rendering {
    class RenderGraph;
}

namespace MeowEngine::Editor {
    /**
     * Handles editor specific rendering like lines, gizmos in world view and rendering order
     */
    class EditorSceneBuilder {
    public:
        EditorSceneBuilder();
        ~EditorSceneBuilder();

        void Init();

    private:
    };
}


#endif //MEOWENGINE_EDITORSCENEBUILDER_HPP

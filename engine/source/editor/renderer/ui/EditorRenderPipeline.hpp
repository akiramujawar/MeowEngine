//
// Created by Akira Mujawar on 22/02/26.
//

#ifndef MEOWENGINE_IEDITORUISYSTEM_HPP
#define MEOWENGINE_IEDITORUISYSTEM_HPP

namespace MeowEngine::Rendering {
    class RenderGraph;
}

namespace MeowEngine::Editor {
    class RenderPipeline {
    public:
        RenderPipeline();
        ~RenderPipeline();

        void BuildGraph(Rendering::RenderGraph& graph);
    };
}


#endif //MEOWENGINE_IEDITORUISYSTEM_HPP

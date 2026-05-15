//
// Created by Akira Mujawar on 13/05/26.
//

#ifndef MEOWENGINE_RENDERGRAPH_HPP
#define MEOWENGINE_RENDERGRAPH_HPP

namespace MeowEngine::Rendering {
    /**
     * Builds the render order for execution of render commands
     * e.g. clear -> draw editor -> then game give -> then editor gizmos etc...
     */
    class RenderGraph {
    public:
        RenderGraph();
        ~RenderGraph();

        void Build();
        void Execute();
    };
}


#endif //MEOWENGINE_RENDERGRAPH_HPP
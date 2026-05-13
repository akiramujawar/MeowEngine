//
// Created by Akira Mujawar on 13/05/26.
//

#ifndef MEOWENGINE_RENDERGRAPH_HPP
#define MEOWENGINE_RENDERGRAPH_HPP

namespace MeowEngine::Shared {
    class RenderGraph {
    public:
        RenderGraph();
        ~RenderGraph();

        void Build();
        void Execute();
    };
}


#endif //MEOWENGINE_RENDERGRAPH_HPP
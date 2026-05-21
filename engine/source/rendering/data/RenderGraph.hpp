//
// Created by Akira Mujawar on 13/05/26.
//

#ifndef MEOWENGINE_RENDERGRAPH_HPP
#define MEOWENGINE_RENDERGRAPH_HPP

#include <vector>

namespace MeowEngine::Rendering {
    class RenderSceneData;
    class IRenderPass;
    struct RenderContext;

    /**
     * Builds the render order for execution of render commands
     * e.g. clear -> draw editor -> then game give -> then editor gizmos etc...
     * essentially the order of execution for the passes
     */
    class RenderGraph {
    public:
        RenderGraph();
        ~RenderGraph();

        void Clear();
        template<typename PassType>
        void Add();
        void Execute(RenderContext& renderContext);

    private:
        std::vector<IRenderPass*> RenderPasses;
    };
}

#endif //MEOWENGINE_RENDERGRAPH_HPP
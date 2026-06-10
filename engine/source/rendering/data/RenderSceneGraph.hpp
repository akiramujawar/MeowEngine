//
// Created by Akira Mujawar on 13/05/26.
//

#ifndef MEOWENGINE_RENDERSCENEGRAPH_HPP
#define MEOWENGINE_RENDERSCENEGRAPH_HPP

#include <vector>

namespace MeowEngine::Rendering {
    struct RenderSceneData;
    class IRenderPass;
    struct RenderContext;

    /**
     * Builds the render order for execution of render commands
     * e.g. clear -> draw editor -> then game give -> then editor gizmos etc...
     * essentially the order of execution for the passes
     */
    class RenderSceneGraph {
    public:
        RenderSceneGraph();
        ~RenderSceneGraph();

        void Clear();
        template<typename PassType>
        void Add();

        void Execute(RenderContext& renderContext);

    private:
        std::vector<std::unique_ptr<IRenderPass>> RenderPasses;
    };

    template <typename PassType>
    void RenderSceneGraph::Add() {
        RenderPasses.emplace_back(std::make_unique<PassType>());
    }
}

#endif //MEOWENGINE_RENDERSCENEGRAPH_HPP
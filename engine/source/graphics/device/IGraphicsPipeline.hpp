//
// Created by Akira Mujawar on 13/05/26.
//

#ifndef MEOWENGINE_IGRAPHICSPIPELINE_HPP
#define MEOWENGINE_IGRAPHICSPIPELINE_HPP

/**
 * This is a compiled format for shaders, topology etc...
 * essentially our render pipelines->pass utilise these compiled formats
 */
namespace MeowEngine::Graphics {
    /**
     * will have blend state, cull mode, fill mode, depth test etc...
     * (backends: GLGraphicsPipeline & VKGraphicsPipeline)
     */
    class IGraphicsPipeline {
    public:
        IGraphicsPipeline();
        ~IGraphicsPipeline();
    };
}


#endif //MEOWENGINE_IGRAPHICSPIPELINE_HPP
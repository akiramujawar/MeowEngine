//
// Created by Akira Mujawar on 14/05/26.
//

#ifndef MEOWENGINE_IRENDERAPI_HPP
#define MEOWENGINE_IRENDERAPI_HPP

#include <memory>

#include "ISceneFrameBuffer.hpp"


namespace MeowEngine::Graphics {
    class GraphicsDevice;
}

namespace MeowEngine::Rendering {
    /**
     * Abstract functionality which needs to be implemented by Graphics API like opengl or vulkan
     */
    class IRenderAPI {
    public:
        virtual ~IRenderAPI() = default;

        /**
         * Clears screen space
         */
        virtual void Clear() = 0;
        virtual void SetViewportSize(int width, int height) = 0;

        virtual std::shared_ptr<ISceneFrameBuffer> GetSceneFrameBuffer() = 0;
    };
}

#endif //MEOWENGINE_IRENDERAPI_HPP
//
// Created by Akira Mujawar on 14/05/26.
//

#ifndef MEOWENGINE_IRENDERAPI_HPP
#define MEOWENGINE_IRENDERAPI_HPP

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
    };
}

#endif //MEOWENGINE_IRENDERAPI_HPP
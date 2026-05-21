//
// Created by Akira Mujawar on 21/05/26.
//

#ifndef MEOWENGINE_IRENDERHANDLE_HPP
#define MEOWENGINE_IRENDERHANDLE_HPP

#include <functional>
#include <AssetHandle.hpp>

namespace MeowEngine::Rendering {
    /**
     * Container for UUID
     * NOTE: Use instead of path or string
     */
    struct IRenderHandle {
        virtual ~IRenderHandle() = default;
    };
}

#endif //MEOWENGINE_IRENDERHANDLE_HPP
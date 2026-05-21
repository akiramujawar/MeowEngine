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
        IRenderHandle();
        virtual ~IRenderHandle() = default;

        uint64_t GetUUID() const;

        bool operator==(const IRenderHandle& handle) const;
        bool operator!=(const IRenderHandle& handle) const;

    private:
        uint64_t UUID;
    };
}

namespace std {
    template<>
    struct std::hash<MeowEngine::Rendering::IRenderHandle> {
        std::size_t operator()(const MeowEngine::Rendering::IRenderHandle& handle) const noexcept {
            return std::hash<uint64_t>()(handle.GetUUID());
        }
    };
}

#endif //MEOWENGINE_IRENDERHANDLE_HPP
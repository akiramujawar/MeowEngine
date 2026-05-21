//
// Created by Akira Mujawar on 11/03/26.
//

#ifndef MEOWENGINE_ASSETHANDLE_HPP
#define MEOWENGINE_ASSETHANDLE_HPP

// #include <cstdlib>
#include <functional>

namespace MeowEngine::Asset {
    /**
     * Container for UUID
     * NOTE: Use instead of path or string
     */
    struct AssetHandle {
        AssetHandle();
        ~AssetHandle();

        /**
         * When a reference is not assigned
         */
        static AssetHandle Null;
        bool IsValid() const;
        uint64_t GetUUID() const;

        bool operator==(const AssetHandle& handle) const;
        bool operator!=(const AssetHandle& handle) const;

    private:
        uint64_t UUID;
    };
}

namespace std {
    template<>
    struct std::hash<MeowEngine::Asset::AssetHandle> {
        std::size_t operator()(const MeowEngine::Asset::AssetHandle& assetHandle) const noexcept {
            return std::hash<uint64_t>()(assetHandle.GetUUID());
        }
    };
}

#endif //MEOWENGINE_ASSETHANDLE_HPP
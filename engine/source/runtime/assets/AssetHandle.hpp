//
// Created by Akira Mujawar on 11/03/26.
//

#ifndef MEOWENGINETEST2_ASSETHANDLE_HPP
#define MEOWENGINETEST2_ASSETHANDLE_HPP

// #include <cstdlib>
#include <functional>

namespace MeowEngine::Runtime::Asset {
    /**
     * Container for UUID
     * NOTE: Use instead of path or string
     */
    struct AssetHandle {
        AssetHandle();
        ~AssetHandle();

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
    struct std::hash<MeowEngine::Runtime::Asset::AssetHandle> {
        std::size_t operator()(const MeowEngine::Runtime::Asset::AssetHandle& assetHandle) const noexcept {
            return std::hash<uint64_t>()(assetHandle.GetUUID());
        }
    };
}

#endif //MEOWENGINETEST2_ASSETHANDLE_HPP
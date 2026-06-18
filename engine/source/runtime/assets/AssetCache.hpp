//
// Created by Akira Mujawar on 05/03/26.
//

#ifndef MEOWENGINE_ASSETCACHE_HPP
#define MEOWENGINE_ASSETCACHE_HPP

#include <cassert>
#include <unordered_map>
#include <memory>

#include <AssetHandle.hpp>
#include <IAsset.hpp>

#include "World.hpp"

namespace MeowEngine::Asset {
    class AssetCache {
    public:
        [[nodiscard]] bool Has(const AssetHandle& handle) const;

        template <typename AssetType>
        AssetType& Get(const AssetHandle& handle) {
            const auto iterator = CacheMap.find(handle);
            assert(iterator != CacheMap.end());

            return *dynamic_cast<AssetType*>(iterator->second.get());
        }

        void Add(const AssetHandle& handle, std::unique_ptr<IAsset> asset) {
            CacheMap.emplace(handle, std::move(asset));
        }

        void Replace(const AssetHandle& handle, std::unique_ptr<IAsset> asset) {
            CacheMap[handle] = std::move(asset);
        }

        void Remove(const AssetHandle& handle) {
            CacheMap.erase(handle);
        }

        void UpdateKey(const AssetHandle& handle) {
            // only internal pointers are unliked so no copy/move is performed here
            auto asset = CacheMap.extract(handle);

            if (!asset.empty()) {
                asset.key() = handle;
                CacheMap.insert(std::move(asset));
            }
        }

        void Clear() {
            CacheMap.clear();
        }

    private:
        std::unordered_map<AssetHandle, std::unique_ptr<IAsset>> CacheMap;
    };
}


#endif //MEOWENGINE_ASSETCACHE_HPP
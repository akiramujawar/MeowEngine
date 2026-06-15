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

namespace MeowEngine::Asset {
    class AssetCache {
    public:
        bool Has(const AssetHandle& handle) const;

        template <typename Asset>
        Asset& GetAsset(AssetHandle& handle) {
            const auto iterator = CacheMap.find(handle);
            assert(iterator != CacheMap.end());
            auto asset = *iterator->second;

            return static_cast<Asset&>(asset);
        }

        void AddAsset() {
            // recieves asset
            // handle
        }

    private:
        std::unordered_map<AssetHandle, std::unique_ptr<IAsset>> CacheMap;
    };
}


#endif //MEOWENGINE_ASSETCACHE_HPP
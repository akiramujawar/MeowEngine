//
// Created by Akira Mujawar on 05/03/26.
//

#include "AssetCache.hpp"

namespace MeowEngine::Asset {
    bool AssetCache::Has(const AssetHandle& handle) const {
        const auto iterator = CacheMap.find(handle);
        return iterator != CacheMap.end();
    }
}

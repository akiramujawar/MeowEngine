//
// Created by Akira Mujawar on 05/03/26.
//

#include <AssetRegistry.hpp>
#include <log.hpp>

namespace MeowEngine::Runtime::Asset {
        void AssetRegistry::Add(const uint64_t uuid, const AssetEntry& entry) {
            ResolverMap[uuid] = entry;
        }

        void AssetRegistry::Remove(const uint64_t uuid) {
            ResolverMap.erase(uuid);
        }

        void AssetRegistry::Resolve() {
            MeowEngine::Log("AssetResolver", "Resolve: Not implemented", LogType::ERROR);
        }
}
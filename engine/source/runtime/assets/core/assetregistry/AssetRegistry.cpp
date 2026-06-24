//
// Created by Akira Mujawar on 05/03/26.
//

#include <AssetRegistry.hpp>
#include <log.hpp>

#include <unordered_set>

namespace MeowEngine::Asset {
    void AssetRegistry::Add(const AssetHandle& handle, const AssetMetadata& entry) {
        if (Has(handle)) {
            MeowEngine::Log("Asset", "Already Exists" + entry.Path, LogType::WARNING);
            return;
        }

        PathMap.try_emplace(Path{entry.Path}, entry);
        MetadataMap.try_emplace(handle, entry);
    }

    void AssetRegistry::Remove(const AssetHandle& handle) {
        auto metadata = MetadataMap.find(handle)->second;

        PathMap.erase(Path{metadata.Path});
        MetadataMap.erase(handle);
    }

    void AssetRegistry::Clear() {
        PathMap.clear();
        MetadataMap.clear();
    }

    std::unordered_map<AssetHandle, AssetMetadata>& AssetRegistry::GetMap() {
        return MetadataMap;
    }

    const std::unordered_map<AssetHandle, AssetMetadata>& AssetRegistry::GetMap() const {
        return MetadataMap;
    }

    uint32_t AssetRegistry::GetSize() const {
        return MetadataMap.size();
    }

    bool AssetRegistry::Has(const AssetHandle& handle) const {
        const auto iterator = MetadataMap.find(handle);
        return iterator != MetadataMap.end();
    }

    bool AssetRegistry::Has(const Path& path) const {
        const auto iterator = PathMap.find(path);
        return iterator != PathMap.end();
    }

    const Path& AssetRegistry::GetPath(const AssetHandle& handle) const {
        return Path {GetMetadata(handle).Path};
    }

    AssetType AssetRegistry::GetType(const AssetHandle& handle) const {
        return GetMetadata(handle).Type;
    }

    const AssetMetadata& AssetRegistry::GetMetadata(const AssetHandle& handle) {
        const auto iterator = MetadataMap.find(handle);
        assert(iterator != MetadataMap.end());

        return iterator->second;
    }

    const AssetMetadata& AssetRegistry::GetMetadata(const Path& path) const {
        const auto iterator = PathMap.find(path);
        assert(iterator != PathMap.end());

        return iterator->second;
    }

    const AssetMetadata& AssetRegistry::GetMetadata(const AssetHandle& handle) const {
        const auto iterator = MetadataMap.find(handle);
        assert(iterator != MetadataMap.end());

        return iterator->second;
    }
}



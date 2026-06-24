//
// Created by Akira Mujawar on 15/06/26.
//

#ifndef MEOWENGINE_ASSETRESOLVER_HPP
#define MEOWENGINE_ASSETRESOLVER_HPP

#include <unordered_set>

#include "Public/Core/Forward.hpp"
#include "AssetRegistry.hpp"

namespace MeowEngine::Asset {
    /**
     * Tracks, Adds, Removes asset handle & metadata
     * Use this to find the path or type of asset handle (stored in metadata)
     */
    class AssetDatabase {
    public:
        AssetDatabase();
        ~AssetDatabase();

        void Load();

        [[nodiscard]] bool Has(const AssetHandle& handle) const;
        [[nodiscard]] bool Has(const Path& handle) const;

        [[nodiscard]] Path GetAssetPath(const AssetHandle& handle) const;
        [[nodiscard]] AssetMetadata GetAssetMetadata(const AssetHandle& handle) const;
        [[nodiscard]] AssetMetadata GetAssetMetadata(const Path& path) const;

        AssetHandle Add(const Path& path);
        void Remove(const AssetHandle& handle);

        /**
         * Call when assets where externally moved / added / deleted
         */
        void Rebuild();

    private:
        [[nodiscard]] static bool IsEnginePath(const Path& path);
        void UpdateAssetHandles(const Path& path, AssetRegistry& assetRegistry);
        void CheckDirectoryForAssetHandles(const Path& directoryPath, AssetRegistry& assetRegistry, std::unordered_set<AssetHandle>& verifiedHandles);

    private:
        AssetRegistry EngineRegistry;
        AssetRegistry SandboxRegistry;
    };
}

#endif //MEOWENGINE_ASSETRESOLVER_HPP
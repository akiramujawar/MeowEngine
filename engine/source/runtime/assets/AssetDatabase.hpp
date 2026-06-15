//
// Created by Akira Mujawar on 15/06/26.
//

#ifndef MEOWENGINE_ASSETRESOLVER_HPP
#define MEOWENGINE_ASSETRESOLVER_HPP

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

        bool Has(const AssetHandle& handle);

        Path GetAssetPath(const AssetHandle& handle);
        AssetMetadata GetAssetMetadata(const AssetHandle& asset);

        void Add(const AssetHandle& handle);
        void Remove(const AssetHandle& handle);

        /**
         * Call when assets where externally moved / added / deleted
         */
        void RebuildE();

    private:
        AssetRegistry EngineRegistry;
        AssetRegistry SandboxRegistry;
    };
}

#endif //MEOWENGINE_ASSETRESOLVER_HPP
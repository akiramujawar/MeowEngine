//
// Created by Akira Mujawar on 05/03/26.
//

#ifndef MEOWENGINE_ASSETREGISTRY_HPP
#define MEOWENGINE_ASSETREGISTRY_HPP

#include <unordered_map>

#include "Public/Core/Include.hpp"
#include "AssetMetadata.hpp"
#include "AssetHandle.hpp"

namespace MeowEngine::Asset {
    /**
     * Tracks all .meowasset files in the project & using UUID
     */
    class AssetRegistry {
    public:
        /**
         * Adds uuid to map & re-writes project asset resolver
         * @param handle
         * @param entry
         */
        void Add(const AssetHandle& handle, const AssetMetadata& entry);

        /**
         * Removes uuid from map & re-writes project asset resolver
         * @param handle
         */
        void Remove(const AssetHandle& handle);

        /**
         * Removes all entries
         */
        void Clear();

        [[nodiscard]] std::unordered_map<AssetHandle, AssetMetadata>& GetMap();
        [[nodiscard]] const std::unordered_map<AssetHandle, AssetMetadata>& GetMap() const;

        [[nodiscard]] uint32_t GetSize() const;
        [[nodiscard]] bool Has(const AssetHandle& handle) const;
        [[nodiscard]] bool Has(const Path& path) const;

        [[nodiscard]] const Path& GetPath(const AssetHandle& handle) const;
        [[nodiscard]] AssetType GetType(const AssetHandle& handle) const;

        [[nodiscard]] const AssetMetadata& GetMetadata(const AssetHandle& handle);
        [[nodiscard]] const AssetMetadata& GetMetadata(const Path& path) const;
        [[nodiscard]] const AssetMetadata& GetMetadata(const AssetHandle& handle) const;


        // AssetCreator.hpp - creates engine types like resolver.txt, world etc...
        // AssetParser.hpp - can be the asset loader itself
        // World.hpp - representation of asset.meowdata world
        // AssetResolver.hpp - is a exception which will load / parse / convert to engine format internally
        // AssetOpener.hpp - opens the clicked file into it's respective requirement (think)

        // parsers
        // asset resolver parser
        // world resolver parser

        // on double click
        // based on asset it should open
        // redirect
    private:
        std::unordered_map<AssetHandle, AssetMetadata> MetadataMap;
        std::unordered_map<Path, AssetMetadata> PathMap;
    };
}


#endif //MEOWENGINE_ASSETREGISTRY_HPP
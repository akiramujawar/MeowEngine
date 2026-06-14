//
// Created by Akira Mujawar on 05/03/26.
//

#ifndef MEOWENGINE_ASSETRESOLVER_HPP
#define MEOWENGINE_ASSETRESOLVER_HPP

#include <map>
#include <AssetEntry.hpp>

namespace MeowEngine::Runtime::Asset {
    /**
     * Tracks all .meowasset files in the project & using UUID
     */
    struct AssetRegistry {
    public:
        /**
         * Adds uuid to map & re-writes project asset resolver
         * @param uuid
         * @param entry
         */
        void Add(const uint64_t uuid, const AssetEntry& entry);

        /**
         * Removes uuid from map & re-writes project asset resolver
         * @param uuid
         */
        void Remove(const uint64_t uuid);

        /**
         * TODO: Manual resolver, incase files where added / moved outside engine
         */
        void Resolve();

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

        std::map<uint64_t, AssetEntry> ResolverMap;
    };
}


#endif //MEOWENGINE_ASSETRESOLVER_HPP
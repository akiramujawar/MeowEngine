//
// Created by Akira Mujawar on 11/03/26.
//

#ifndef MEOWENGINETEST_ASSETREGISTRYSERIALIZER_HPP
#define MEOWENGINETEST_ASSETREGISTRYSERIALIZER_HPP

#include "Public/Core/Forward.hpp"

#include <AssetRegistry.hpp>


namespace MeowEngine::Asset {
    /**
     * TODO: try using yaml / json for this
     */
    class AssetRegistrySerializer {
    public:
        /**
         * Creates temp file, moves header & writes asset resolver map
         */
        static bool Serialize(const Path& resolverPath, const AssetRegistry& resolverAsset);

        /**
         * Loads asset resolver (.meowreg) & caches into asset resolver map
         */
        static bool Deserialize(const Path& resolverPath, AssetRegistry& resolverAsset);

    private:
        /**
         * Creates a new .meowproject with header
         * NOTE: Currently we dont have a layer to create new project hence we give a hard name "example"
         * @param path
         */
        static void Create(const Path& path);
    };
}


#endif //MEOWENGINETEST_ASSETREGISTRYSERIALIZER_HPP
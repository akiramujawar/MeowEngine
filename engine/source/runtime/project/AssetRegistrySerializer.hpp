//
// Created by Akira Mujawar on 11/03/26.
//

#ifndef MEOWENGINETEST2_ASSETRESOLVERSERIALIZER_HPP
#define MEOWENGINETEST2_ASSETRESOLVERSERIALIZER_HPP

namespace MeowEngine::Core::IO::FileSystem {
    class Path;
}

// TODO: Do we simply by this by creating hpp/cpp or keep it as it?
namespace MeowEngine {
    namespace FileSystem = Core::IO::FileSystem;
}

namespace MeowEngine::Runtime::Asset {
    struct AssetRegistry;
}

namespace MeowEngine::Runtime::Asset::Serializer {
    class AssetRegistrySerializer {
    public:
        /**
         * Creates temp file, moves header & writes asset resolver map
         */
        static void Serialize(const FileSystem::Path& resolverPath, const AssetRegistry& resolverAsset);

        /**
         * Loads asset resolver (.meowproject) & caches into asset resolver map
         */
        static void Deserialize(const FileSystem::Path& resolverPath, AssetRegistry& resolverAsset);

    private:
        /**
         * Creates a new .meowproject with header
         * NOTE: Currently we dont have a layer to create new project hence we give a hard name "example"
         * @param path
         */
        static void Create(const FileSystem::Path& path);
    };
}


#endif //MEOWENGINETEST2_ASSETRESOLVERSERIALIZER_HPP
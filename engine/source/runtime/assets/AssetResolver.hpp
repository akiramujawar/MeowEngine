//
// Created by Akira Mujawar on 05/03/26.
//

#ifndef MEOWENGINE_ASSETRESOLVER_HPP
#define MEOWENGINE_ASSETRESOLVER_HPP

#include <map>
#include <string>

namespace MeowEngine::Core::IO::FileSystem {
    class Path;
}

// TODO: Do we simply by this by creating hpp/cpp or keep it as it?
namespace MeowEngine {
    namespace FileSystem = Core::IO::FileSystem;
}

namespace MeowEngine::Runtime::Asset {
    class Path;

    /**
     * Tracks all .meowasset files in the project & using UUID
     */
    class AssetResolver {
    public:
        /**
         * Loads (if not exists Create) .meowproject
         * NOTE: Currently we dont have a layer to create new project hence we give a hard name "example"
         */
        void Init();

        /**
         * Creates a new .meowproject with header
         * NOTE: Currently we dont have a layer to create new project hence we give a hard name "example"
         * @param path
         */
        static void Create(const FileSystem::Path& path);

        /**
         * Loads asset resolver (.meowproject) & caches into asset resolver map
         */
        void Load();

        /**
         * Creates temp file, moves header & writes asset resolver map
         */
        void Save();

        /**
         * Adds uuid to map & re-writes project asset resolver
         * @param uuid
         * @param path
         */
        void Add(const uint64_t uuid, const std::string& path);

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


    private:
        std::string ResolverPath;
        std::map<uint64_t, std::string> ResolverMap;
    };
}


#endif //MEOWENGINE_ASSETRESOLVER_HPP
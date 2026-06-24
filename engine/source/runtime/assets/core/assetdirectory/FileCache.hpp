//
// Created by Akira Mujawar on 24/06/26.
//

#ifndef MEOWENGINE_FILECACHE_HPP
#define MEOWENGINE_FILECACHE_HPP

#include <unordered_map>
#include <vector>

#include "DirectoryAsset.hpp"

namespace MeowEngine::Asset {
    using AssetMap = std::unordered_map<Path, std::vector<DirectoryAsset>>;
    class AssetDatabase;

    class FileCache {
    public:
        bool HasFile(const Path& path);
        bool IsValidFolder(const Path& path);
        std::vector<DirectoryAsset> Get(const Path& path);
        std::vector<DirectoryAsset> LoadAndGet(const Path& path);
        void Clear();

    private:
        AssetMap Files;
    };
}

#endif //MEOWENGINE_FILECACHE_HPP
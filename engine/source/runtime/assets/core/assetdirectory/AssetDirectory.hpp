//
// Created by Akira Mujawar on 15/06/26.
//

#ifndef MEOWENGINE_ASSETDIRECTORY_HPP
#define MEOWENGINE_ASSETDIRECTORY_HPP

#include <map>

#include "DirectoryFolder.hpp"

namespace MeowEngine::Asset {
    /**
     * NOTE: use this for reading file system (in asset panel)
     */
    class AssetDirectory {
    public:
        AssetDirectory() = default;
        ~AssetDirectory() = default;

        void Init();
        void Load();

        std::vector<std::string> GetPaths(std::string path);

    private:
        std::map<std::string, DirectoryFolder> Views;
    };
}


#endif //MEOWENGINE_ASSETDIRECTORY_HPP
//
// Created by Akira Mujawar on 15/06/26.
//

#ifndef MEOWENGINE_DIRECTORYFOLDER_HPP
#define MEOWENGINE_DIRECTORYFOLDER_HPP

#include <vector>

namespace MeowEngine::Asset {
    struct DirectoryFolder {
        std::string Path;

        std::vector<std::string> AssetPaths;
    };
}


#endif //MEOWENGINE_DIRECTORYFOLDER_HPP
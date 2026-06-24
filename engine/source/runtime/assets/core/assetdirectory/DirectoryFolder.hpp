//
// Created by Akira Mujawar on 15/06/26.
//

#ifndef MEOWENGINE_DIRECTORYFOLDER_HPP
#define MEOWENGINE_DIRECTORYFOLDER_HPP

#include <vector>
#include "Public/Core/Forward.hpp"

namespace MeowEngine::Asset {
    struct DirectoryFolder {
        std::vector<Path> Folders;
    };
}


#endif //MEOWENGINE_DIRECTORYFOLDER_HPP
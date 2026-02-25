//
// Created by Akira Mujawar on 24/02/26.
//

#ifndef MEOWENGINE_DIRECTORY_HPP
#define MEOWENGINE_DIRECTORY_HPP

#include "filesystem"
#include "vector"

#include "Path.hpp"

namespace MeowEngine::Core::IO::FileSystem {

    class Directory {
    public:
        explicit Directory(const Path& pPath);

        bool Exists() const;
        bool Create();
        bool Remove();

        std::vector<Path> GetFiles(bool pIncludeSubDirectories) const;
        std::vector<Path> GetDirectories(bool pIncludeSubDirectories) const;

        const Path& GetPath() const;

    private:
        Path CurrentPath;

    };

}


#endif //MEOWENGINE_DIRECTORY_HPP

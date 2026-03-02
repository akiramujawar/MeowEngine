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
        explicit Directory(const Path& path);
        
        bool Exists() const;
        bool Create();
        bool Remove();

        std::vector<Path> GetFiles(bool includeSubDirectories) const;
        std::vector<Path> GetDirectories(bool includeSubDirectories) const;
        std::vector<Path> GetAll(bool includeSubDirectories) const;

        const Path& GetPath() const;

    private:
        Path CurrentPath;

    };

}


#endif //MEOWENGINE_DIRECTORY_HPP

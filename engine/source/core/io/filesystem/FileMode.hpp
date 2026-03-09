//
// Created by Akira Mujawar on 24/02/26.
//

#ifndef MEOWENGINE_FILEMODE_HPP
#define MEOWENGINE_FILEMODE_HPP

namespace MeowEngine::Core::IO::FileSystem {

    enum class FileMode {
        READ,
        WRITE,
        APPEND,
        READ_WRITE
    };

}

#endif //MEOWENGINE_FILEMODE_HPP

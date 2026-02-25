//
// Created by Akira Mujawar on 24/02/26.
//

#ifndef MEOWENGINE_FILEWATCHEVENT_HPP
#define MEOWENGINE_FILEWATCHEVENT_HPP

namespace MeowEngine::Core::IO::FileSystem {

    enum class FileWatchEvent {
        CREATED,
        MODIFIED,
        DELETED,
        RENAMED
    };

}

#endif //MEOWENGINE_FILEWATCHEVENT_HPP

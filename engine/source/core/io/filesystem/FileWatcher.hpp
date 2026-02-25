//
// Created by Akira Mujawar on 22/02/26.
//

#ifndef MEOWENGINE_FILEWATCHER_HPP
#define MEOWENGINE_FILEWATCHER_HPP

namespace MeowEngine::Core::IO::FileSystem {

    class FileWatcher {
    public:
        FileWatcher();
        ~FileWatcher();

        void Watch();
        void Unwatch();

        void SetCallback();

        void Start();
        void Stop();
    };

}

#endif //MEOWENGINE_FILEWATCHER_HPP

//
// Created by Akira Mujawar on 09/06/26.
//

#ifndef MEOWENGINE_TRACYPROFILER_HPP
#define MEOWENGINE_TRACYPROFILER_HPP

#include <sys/_types/_pid_t.h>

namespace MeowEngine::Editor {
    class TracyProfiler {
    public:
        TracyProfiler();
        ~TracyProfiler();

        static void HandleTracyProfilerSignal(int signal);

        void Open();
        void Close();

    private:
        static pid_t ProcessID;
    };
}


#endif //MEOWENGINE_TRACYPROFILER_HPP
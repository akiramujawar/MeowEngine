//
// Created by Akira Mujawar on 09/06/26.
//

#ifndef MEOWENGINE_TRACYPROFILER_HPP
#define MEOWENGINE_TRACYPROFILER_HPP

#if (!__WEB__)
#include <sys/_types/_pid_t.h>
#endif

namespace MeowEngine::Editor {
    class TracyProfiler {
    public:
        TracyProfiler();
        ~TracyProfiler();

        static void HandleTracyProfilerSignal(int signal);

        void Open();
        void Close();

    private:
    #if (__WEB__)
        static int ProcessID;
    #else
        static pid_t ProcessID;
    #endif
    };
}


#endif //MEOWENGINE_TRACYPROFILER_HPP
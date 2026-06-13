//
// Created by Akira Mujawar on 09/06/26.
//

#include <TracyProfiler.hpp>

#include <sys/wait.h> // For waitpid()
#include <unistd.h> // For fork(), exec()
#include <csignal> // For signal handling
#include <cstdlib>
#include <system_error>

namespace  MeowEngine::Editor {
    #if (__WEB__)
        int TracyProfiler::ProcessID = -1;
    #else
        pid_t TracyProfiler::ProcessID = -1;
    #endif

    TracyProfiler::TracyProfiler() {
        ProcessID = -1;
    }

    TracyProfiler::~TracyProfiler() {}

        void TracyProfiler::HandleTracyProfilerSignal(int signal) {
            if (ProcessID > 0) {
                kill(ProcessID, SIGTERM); // Send termination signal to child
                waitpid(ProcessID, nullptr, 0); // Wait for child to terminate
            }
    //        exit(0); // Exit the parent process // shouldn't do this or the application destruction won't happen
        }

    void TracyProfiler::Open() {
        // Register signal handlers to clean up child process on exit
        signal(SIGINT, &HandleTracyProfilerSignal);  // Handle Ctrl+C
        signal(SIGTERM, &HandleTracyProfilerSignal); // Handle termination signals
        signal(SIGQUIT, &HandleTracyProfilerSignal); // Handle quit signals

        ProcessID = fork();

        if (ProcessID == -1) {
            perror("fork");
            exit(1);
        }

        if (ProcessID == 0) {
            // Child process
            const char* path = "dependencies/profiler/build/unix/Tracy-release";
            if (execl(path, path, (char*) NULL) == -1) {
                perror("execl");
                exit(1);
            }
        }
    }

    void TracyProfiler::Close() {
        // SIGQUIT
        if (ProcessID > 0) {
            kill(ProcessID, SIGTERM); // Send termination signal to child
            waitpid(ProcessID, nullptr, 0); // Wait for child to terminate
        }
        //        exit(0); // Exit the parent process // shouldn't do this or the application destruction won't happen
    }
}

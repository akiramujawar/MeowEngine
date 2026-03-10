//
// Created by Akira Mujawar on 06/07/22.
//

#include "Application.hpp"

#include "opengl_app_multi_thread.hpp"
#include "opengl_app_web.hpp"

#include "log.hpp"

#include <stdexcept>
#include <string>

using MeowEngine::Application;

struct Application::Internal {
    const std::string classLogTag;

    Internal() : classLogTag("MeowEngine::Engine::") {}

    void Run() {
        PT_PROFILE_SCOPE;
        static const std::string logTag{classLogTag + "run"};

        MeowEngine::Log(logTag, "Initializing Engine...");

        ResolveApplication()->CreateApplication();
    }

    // we are using unique_ptr smart pointer as a return value so it will self destruct upon leaving its containing scope
    std::unique_ptr<MeowEngine::Engine> ResolveApplication() {
        PT_PROFILE_SCOPE;
        static const std::string logTag{classLogTag + "resolving Application"};

        try {
#ifndef __EMSCRIPTEN__
            MeowEngine::Log(logTag, "Creating OpenGL Multi Threaded Application...");
            return std::make_unique<MeowEngine::OpenGLAppMultiThread>();
#else
            MeowEngine::Log(logTag, "Creating OpenGL Web Application...");
            return std::make_unique<MeowEngine::OpenGLAppWeb>();
#endif
        }
        catch (const std::exception& error) {
            MeowEngine::Log(logTag, "OpenGL Application failed to initialized.", error);
        }

        throw std::runtime_error(logTag + " No application can run on current environment");
    }

    ~Internal() {
        MeowEngine::Log("Engine", "Quit");
//        SDL_Quit();
    }
};

Application::Application() : InternalPointer(MeowEngine::make_internal_ptr<Internal>()) {}

void Application::Run() {
    InternalPointer->Run();
}


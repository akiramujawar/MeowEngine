//
// Created by Akira Mujawar on 22/10/24.
//
#include "SDL_EngineWindow.hpp"

#include "GL_API.hpp"
#include <EmscriptenAPI.hpp>

#include "Public/Core/Include.hpp"
#include "SDL_NativeFileDialog.hpp"
#include "PlatformType.hpp"

namespace MeowEngine::Platform {

    SDL_EngineWindow::SDL_EngineWindow()
        : Handle(CreateHandle(SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI)),
          Context(CreateContext()) {}

    SDL_EngineWindow::~SDL_EngineWindow() {
        MeowEngine::Log("Window", "Destroyed");
        
        SDL_NativeFileDialog::Quit();

        SDL_GL_DeleteContext(Context);
        SDL_DestroyWindow(Handle);

        SDL_Quit();
    }

    void SDL_EngineWindow::SwapWindow() const {
        SDL_GL_SwapWindow(Handle);
    }

    Vector2Int SDL_EngineWindow::GetWindowSize() {
#ifdef __WEB__
        // For Emscripten targets we will invoke some Javascript
        // to find out the dimensions of the canvas in the HTML
        // document. Note that the 'width' and 'height' attributes
        // need to be set on the <canvas /> HTML element, like so:
        // <canvas id="canvas" width="600", height="360"></canvas>

        int width = static_cast<int>(EM_ASM_INT({
            return document.getElementById('canvas').width;
        }));

        int height = static_cast<int>(EM_ASM_INT({
            return document.getElementById('canvas').height;
        }));

        return Vector2Int{width, height};
#else
        int width {0};
        int height {0};

        SDL_GetWindowSize(Handle, &width, &height);
        return Vector2Int{width, height};

#endif
    }

    void SDL_EngineWindow::ClearContext() const {
        SDL_GL_MakeCurrent(Handle, nullptr);
    }

    void SDL_EngineWindow::MakeCurrent() const {
        SDL_GL_MakeCurrent(Handle, Context);
    }

    SDL_Window* SDL_EngineWindow::GetHandle() const {
        return Handle;
    }

    SDL_GLContext SDL_EngineWindow::GetContext() const {
        return Context;
    }

    SDL_Window* SDL_EngineWindow::CreateHandle(const uint32_t& windowFlags){
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
            throw std::runtime_error("Main Thread:: Could not initialize VIDEO & EVENTS");
        }

        if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
            std::cout << "SDL_image error: " << IMG_GetError() << std::endl;
            MeowEngine::Log("SDL Image error", IMG_GetError(), LogType::ERROR);
            throw std::runtime_error("Main Thread:: Could not initialize SDL2_image");
        }
    
        SDL_NativeFileDialog::Init();

        MeowEngine::Log("Main Thread", "SDL2 Initialized");

        // Enable double buffering (this is usually the default)
        // 1: Enable VSync || 0: Disable VSync
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        Vector2Int windowSize{GetInitialWindowSize()};


#ifdef __EMSCRIPTEN__
        // GL 3.0 + GLSL 130
//        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    //    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    //    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    //    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#else
        // Set the attributes for SDL (here we are supporting from 1.0 to 4.0 version of shader)
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif

//    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
//    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
//    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
//    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
//    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

        SDL_Window* window{SDL_CreateWindow(
            "MeowEngine",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            windowSize.Width,
            windowSize.Height,
            windowFlags
        )};

        if(ShouldDisplayFullScreen()) {
            SDL_SetWindowFullscreen(window, SDL_TRUE);
        }
        
        return window;
    }

    SDL_GLContext SDL_EngineWindow::CreateContext() {
        static const std::string logTag("MeowEngine::OpenGLApplication::CreateContext");

        SDL_GLContext context {SDL_GL_CreateContext(Handle)};
        SDL_GL_SetSwapInterval(1);// wth si this lol? from 100-450 to 1700 fps?
        SDL_GL_MakeCurrent(Handle, context);

        // TODO: This is opengl specific move it outside
#ifdef WIN32
        glewInit();
#endif
        glClearDepthf(1.0f);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glEnable(GL_CULL_FACE);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        MeowEngine::Log(logTag, "Context Created");

        // Check WebGL version
        const char* version = (const char*)glGetString(GL_VERSION);
        MeowEngine::Log("MeowEngine::graphics::OpenGLFrameBuffer: WEBGL Version", version);

        return context;
    }

    void SDL_EngineWindow::OpenURL(const WebAddress& address) {
        SDL_OpenURL(address.CStr());
    }

    bool SDL_EngineWindow::ShouldDisplayFullScreen() {
        switch (MeowEngine::GetCurrentPlatform()) {
            case MeowEngine::PlatformType::ios:
                return true;
            case MeowEngine::PlatformType::android:
                return true;
            case MeowEngine::PlatformType::windows:
                return false;
            case MeowEngine::PlatformType::mac:
                return false;
            case MeowEngine::PlatformType::emscripten:
                return false;
        }
    }

    Vector2Int SDL_EngineWindow::GetInitialWindowSize() {
#ifdef __EMSCRIPTEN__
        return GetWindowSize();
#else
        const MeowEngine::PlatformType platform{MeowEngine::GetCurrentPlatform()};

        // For mobile platforms we will fetch the full screen size.
        SDL_DisplayMode displayMode;
        SDL_GetDesktopDisplayMode(0, &displayMode);

        return Vector2Int{displayMode.w, displayMode.h};
#endif

    }

}


//#ifdef __EMSCRIPTEN__
//WindowSize GetEmscriptenCanvasSize() {
//        // For Emscripten targets we will invoke some Javascript
//        // to find out the dimensions of the canvas in the HTML
//        // document. Note that the 'width' and 'height' attributes
//        // need to be set on the <canvas /> HTML element, like so:
//        // <canvas id="canvas" width="600", height="360"></canvas>
//
//        uint32_t width{static_cast<uint32_t>(EM_ASM_INT({
//            return document.getElementById('canvas').width;
//        }))};
//
//        uint32_t height{static_cast<uint32_t>(EM_ASM_INT({
//            return document.getElementById('canvas').height;
//        }))};
//
//        return WindowSize{width, height};
//    };
//#endif
//
// Created by Akira Mujawar on 17/05/26.
//

#include <ImGuiRender.hpp>

#include <ImguiAPI.hpp>
#include <PlatformBridgeAPI.hpp>

#include <GraphicsDevice.hpp>
#include <RendererInitData.hpp>

namespace {
    void LoadIniFromFileSystem() { // used for emscripten only
        const char* iniPath = "assets/layout.ini"; // Path in the virtual filesystem
        if (FILE* file = fopen(iniPath, "r")) {
            fseek(file, 0, SEEK_END);
            size_t size = ftell(file);
            rewind(file);

            char* buffer = new char[size + 1];
            fread(buffer, 1, size, file);
            buffer[size] = '\0'; // Null-terminate the string
            fclose(file);

            ImGui::LoadIniSettingsFromMemory(buffer, size);
            delete[] buffer;

            MeowEngine::Log("ImGUI", "Loaded File");
        }
        else {
            MeowEngine::Log("ImGUI", "Failed to open file");
        }
    }
}

namespace MeowEngine::Rendering {
    ImGuiRender::ImGuiRender(Graphics::GraphicsDevice& device) {
#ifdef __EMSCRIPTEN__
        const char* glsl_version = "#version 300 es";
#else
        const char* glsl_version = "#version 400";
#endif

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends
        ImGui_ImplSDL2_InitForOpenGL(device.GetWindow().GetHandle(), device.GetWindow().GetContext());
        ImGui_ImplOpenGL3_Init(glsl_version);

#ifdef __APPLE__
        createMacMenu();
#elif _WIN32
        SDL_SysWMinfo wmInfo;
        SDL_VERSION(&wmInfo.version);
        SDL_GetWindowWMInfo(window, &wmInfo);
        createWindowsMenu(wmInfo.info.win.window);
#endif
    }

    ImGuiRender::~ImGuiRender() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiRender::Init(RendererInitData& context) {
        ImGuiIO& io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

#ifdef __WEB__
        LoadIniFromFileSystem();
#else
        auto path = context.Project->Settings.GetExecutablePath() + "assets/layout.ini";
        MeowEngine::Log("IMGUI PATH", path.GetRawString());
        io.IniFilename = path.GetRawString().c_str();
        ImGui::LoadIniSettingsFromDisk(io.IniFilename);
#endif
    }

    void ImGuiRender::BeginFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiRender::EndFrame() {
        ImGui::Render();
    }

    void ImGuiRender::DrawFrame() {
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiRender::ProcessInputEvent(const SDL_Event& event) {
        ImGui_ImplSDL2_ProcessEvent(&event);
    }
}

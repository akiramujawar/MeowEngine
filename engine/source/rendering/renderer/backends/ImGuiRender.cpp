//
// Created by Akira Mujawar on 17/05/26.
//

#include <ImGuiRender.hpp>

#include <GraphicsDevice.hpp>
#include <ImguiAPI.hpp>
#include <PlatformBridgeAPI.hpp>

namespace MeowEngine::Rendering {
    ImGuiRender::ImGuiRender(Graphics::GraphicsDevice& device) {
#ifdef __EMSCRIPTEN__
        const char* glsl_version = "#version 300 es";
#else
        const char* glsl_version = "#version 400";
#endif

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        //    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

#ifdef __EMSCRIPTEN__
        LoadIniFromFileSystem();
#else
        io.IniFilename = "assets/layout.ini";
        ImGui::LoadIniSettingsFromDisk(io.IniFilename);
#endif

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

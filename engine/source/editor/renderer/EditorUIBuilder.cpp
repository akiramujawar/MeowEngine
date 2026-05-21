//
// Created by Akira Mujawar on 08/07/24.
//

#include <EditorUIBuilder.hpp>

// #include <ImguiAPI.hpp>
// #include <PlatformBridgeAPI.hpp>

#include <SDL_video.h>
#include <SDL_events.h>

#include <log.hpp>

#include <sys/wait.h> // For waitpid()
#include <unistd.h> // For fork(), exec()
#include <csignal> // For signal handling

#include "GraphicsDevice.hpp"
#include "UserEventType.hpp"

namespace {
    pid_t tracy_profiler_pid = -1;

    static void HandleTracyProfilerSignal(int signal) {
        if (tracy_profiler_pid > 0) {
            kill(tracy_profiler_pid, SIGTERM); // Send termination signal to child
            waitpid(tracy_profiler_pid, nullptr, 0); // Wait for child to terminate
        }
//        exit(0); // Exit the parent process // shouldn't do this or the application destruction won't happen
    }

    void LoadIniFromFileSystem() {
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

namespace MeowEngine::Editor {

    EditorUIBuilder::EditorUIBuilder()
        : WorldInspectorPanel()
        , WorldTreePanel()
        , WorldViewPanel()
        , ConsolePanel()
        , WorldSettingPanel()
        , ProjectSettingPanel()
        , EditorSettingPanel() {

        MeowEngine::Log("ImGuiRenderer", "Creating...");
    }

    EditorUIBuilder::~EditorUIBuilder() {
        MeowEngine::Log("ImGuiRenderer", "Destroying...");
    }

    void EditorUIBuilder::Init(Runtime::GameplaySystem& gameplay) {
        WorldInspectorPanel.Init(gameplay);
        WorldTreePanel.Init(gameplay);
    }

    void EditorUIBuilder::Input(const SDL_Event& event) {
        PT_PROFILE_SCOPE_N("UI Input");;

        ImGui_ImplSDL2_ProcessEvent(&event);

        // Handles custom SDL events
#ifdef _WIN32
        if (event.type == SDL_SYSWMEVENT) {
            if (event.syswm.msg->msg.win.msg == WM_COMMAND) {
                switch (LOWORD(event.syswm.msg->msg.win.wParam)) {
                    case 1:
                        std::cout << "Option 1 selected" << std::endl;
                        break;
                }
            }
        }
#endif

#ifdef __APPLE__
        if (event.type == SDL_USEREVENT) {
            switch (event.user.code) {
                case UserEventType::OPEN_TRACY:
                    OpenTracyProfiler();
                    break;
            }
        }
#endif
    }

    void EditorUIBuilder::BuildDrawData(entt::registry& registry,
                               std::queue<std::shared_ptr<MeowEngine::ReflectionPropertyChange>>& inUIInputQueue,
                               Editor::Selector& pSelection,
                               unsigned int frameBufferId, const double fps) {
        DrawFrame(registry, inUIInputQueue, pSelection, frameBufferId, fps);
    }

    void EditorUIBuilder::ClosePIDs() {
        ::HandleTracyProfilerSignal(SIGQUIT);
    }

//bool MeowEngine::graphics::ImGuiRenderer::IsSceneViewportFocused() const {
//    return isSceneViewportFocused;
//}
//
//const WindowSize& MeowEngine::graphics::ImGuiRenderer::GetSceneViewportSize() const {
//    return SceneViewportSize;
//}

    void EditorUIBuilder::OpenTracyProfiler() {
        // Register signal handlers to clean up child process on exit
        signal(SIGINT, &::HandleTracyProfilerSignal);  // Handle Ctrl+C
        signal(SIGTERM, &::HandleTracyProfilerSignal); // Handle termination signals
        signal(SIGQUIT, &::HandleTracyProfilerSignal); // Handle quit signals

        tracy_profiler_pid = fork();

        if (tracy_profiler_pid == -1) {
            perror("fork");
            exit(1);
        }

        if (tracy_profiler_pid == 0) {
            // Child process
            const char* path = "dependencies/profiler/build/unix/Tracy-release";
            if (execl(path, path, (char*) NULL) == -1) {
                perror("execl");
                exit(1);
            }
        }
    }

    void EditorUIBuilder::DrawFrame(entt::registry& registry,
                                  std::queue<std::shared_ptr<MeowEngine::ReflectionPropertyChange>>& inUIInputQueue,
                                  Editor::Selector& pSelection,
                                  uint32_t frameBufferId, const double fps) {
        DockerSpace.SetupDockingSpace();

        WorldInspectorPanel.Draw(registry, inUIInputQueue, pSelection);
        WorldTreePanel.Draw(registry, pSelection);
        WorldViewPanel.Draw(reinterpret_cast<void*>(frameBufferId), fps);
        WorldSettingPanel.Draw();
        ProjectSettingPanel.Draw();
        EditorSettingPanel.Draw();
        AssetPanel.Draw(pSelection);
        ConsolePanel.Draw();

        // ImGui::ShowDemoWindow(&IsRendering);
    }

}
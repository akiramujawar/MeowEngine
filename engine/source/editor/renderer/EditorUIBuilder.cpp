//
// Created by Akira Mujawar on 08/07/24.
//

#include <EditorUIBuilder.hpp>

#include <log.hpp>
#include <GraphicsDevice.hpp>

namespace {
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
        , EditorSettingPanel()
    {
        MeowEngine::Log("ImGuiRenderer", "Creating...");
    }

    EditorUIBuilder::~EditorUIBuilder() {
        MeowEngine::Log("ImGuiRenderer", "Destroying...");
    }

    void EditorUIBuilder::Init(Runtime::GameplaySystem& gameplay) {
        WorldInspectorPanel.Init(gameplay);
        WorldTreePanel.Init(gameplay);
    }

    void EditorUIBuilder::BuildDrawData(Rendering::RenderContext& renderContext, entt::registry& registry,
                               std::queue<std::shared_ptr<MeowEngine::ReflectionPropertyChange>>& inUIInputQueue,
                               Editor::Selector& pSelection,
                               unsigned int frameBufferId, const double fps) {
        DockerSpace.SetupDockingSpace();

        WorldInspectorPanel.Draw(registry, inUIInputQueue, pSelection);
        WorldTreePanel.Draw(renderContext);
        WorldViewPanel.Draw(reinterpret_cast<void*>(frameBufferId), fps);
        WorldSettingPanel.Draw();
        ProjectSettingPanel.Draw();
        EditorSettingPanel.Draw();
        AssetPanel.Draw(pSelection);
        ConsolePanel.Draw();

        // ImGui::ShowDemoWindow(&IsRendering);
    }

    void EditorUIBuilder::OpenProfiler() {
        Profiler.Open();
    }

    void EditorUIBuilder::CloseProcesses() {
        Profiler.Close();
    }

//bool MeowEngine::graphics::ImGuiRenderer::IsSceneViewportFocused() const {
//    return isSceneViewportFocused;
//}
//
//const WindowSize& MeowEngine::graphics::ImGuiRenderer::GetSceneViewportSize() const {
//    return SceneViewportSize;
//}

}
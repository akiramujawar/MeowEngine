//
// Created by Akira Mujawar on 08/07/24.
//

#ifndef MEOWENGINE_EDITORUIBUILDER_HPP
#define MEOWENGINE_EDITORUIBUILDER_HPP

#include <TracyProfiler.hpp>

#include <ImguiDockerSpace.hpp>
#include "ImguiWorldTreePanel.hpp"
#include "ImguiWorldInspectorPanel.hpp"
#include "ImguiWorldViewPanel.hpp"
#include "ImguiConsolePanel.hpp"
#include "ImguiAssetPanel.hpp"
#include "ImguiWorldSettingPanel.hpp"
#include "ImguiProjectSettingPanel.hpp"
#include "ImguiEditorSettingPanel.hpp"

#include "entt.hpp"
#include "queue"
#include "Selector.hpp"

namespace MeowEngine::Editor {
    /**
     * Screen space UI (tied to imgui) for editor windows, buttons, panels, debugs
     */
    struct EditorUIBuilder {
        EditorUIBuilder();
        ~EditorUIBuilder();

        void Init(Runtime::GameplaySystem& gameplay);
        void BuildDrawData(entt::registry& registry, std::queue<std::shared_ptr<MeowEngine::ReflectionPropertyChange>>& inUIInputQueue, Editor::Selector& pSelection, unsigned int frameBufferId, const double fps);

        void OpenProfiler();

        /**
         * Closes any child processes like tracy
         */
        void CloseProcesses();
//        bool IsSceneViewportFocused() const;
//        const WindowSize& GetSceneViewportSize() const;

    private:
        void DrawFrame(entt::registry& registry, std::queue<std::shared_ptr<MeowEngine::ReflectionPropertyChange>>& inUIInputQueue, Editor::Selector& pSelection, uint32_t frameBufferId, const double fps);

//        bool isSceneViewportFocused; // soon come up with good naming conventions
//        WindowSize SceneViewportSize;

        bool IsRendering;

        TracyProfiler Profiler;

        ImGuiDockerSpace DockerSpace;
        ImGuiWorldTreePanel WorldTreePanel;
        ImGuiWorldInspectorPanel WorldInspectorPanel;
        ImGuiWorldViewPanel WorldViewPanel;
        ImGuiConsolePanel ConsolePanel;
        ImguiAssetPanel AssetPanel;
        ImguiWorldSettingPanel WorldSettingPanel;
        ImguiProjectSettingPanel ProjectSettingPanel;
        ImguiEditorSettingPanel EditorSettingPanel;
    };
}

// setup imgui input
// extract the hierarchy tree elements
// update ui to read from it
// setup the command system for tree selection

#endif //MEOWENGINE_EDITORUIBUILDER_HPP

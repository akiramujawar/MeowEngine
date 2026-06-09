//
// Created by Akira Mujawar on 08/07/24.
//

#ifndef MEOWENGINE_IMGUIEDITORUISYSTEM_HPP
#define MEOWENGINE_IMGUIEDITORUISYSTEM_HPP

//#include <scene.hpp>
// #include "GLWorldViewBuffer.hpp"
// #include "Math.hpp"

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
        void Input(const SDL_Event& event);
        void BuildDrawData(entt::registry& registry, std::queue<std::shared_ptr<MeowEngine::ReflectionPropertyChange>>& inUIInputQueue, Editor::Selector& pSelection, unsigned int frameBufferId, const double fps);

        // Closes any child processes like tracy
        void ClosePIDs();
        void OpenTracyProfiler();
//        bool IsSceneViewportFocused() const;
//        const WindowSize& GetSceneViewportSize() const;

    private:


        // void CreateNewFrame();
        void DrawFrame(entt::registry& registry, std::queue<std::shared_ptr<MeowEngine::ReflectionPropertyChange>>& inUIInputQueue, Editor::Selector& pSelection, uint32_t frameBufferId, const double fps);
        // void RenderFrame();

//        void CreateRender3DPanel(unsigned int frameBufferId);
//        bool isSceneViewportFocused; // soon come up with good naming conventions
//        WindowSize SceneViewportSize;

//        void CreateLifeObjectSelectorPanel(MeowEngine::Scene& scene);
//        void CreateSelectableItem(bool isEnd);
//        const ImGuiTreeNodeFlags SelectableFlags;

//        void CreateObjectEditorPanel(const core::LifeObject& selectedLifeObject);

//        void CreateLogPanel();

        bool IsRendering;

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


#endif //MEOWENGINE_IMGUIEDITORUISYSTEM_HPP

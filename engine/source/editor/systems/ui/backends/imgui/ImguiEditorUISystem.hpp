//
// Created by Akira Mujawar on 08/07/24.
//

#ifndef MEOWENGINE_IMGUIEDITORUISYSTEM_HPP
#define MEOWENGINE_IMGUIEDITORUISYSTEM_HPP

//#include <scene.hpp>
#include "opengl_framebuffer.hpp"
#include "window_size.hpp"

#include "ImguiWorldTreePanel.hpp"
#include "ImguiWorldInspectorPanel.hpp"
#include "ImguiWorldViewPanel.hpp"
#include "ImguiConsolePanel.hpp"
#include "ImguiAssetPanel.hpp"
#include "ImguiWorldSettingPanel.hpp"
#include "ImguiProjectSettingPanel.hpp"
#include "ImguiEditorSettingPanel.hpp"

#include "entt_wrapper.hpp"
#include "queue"
#include "selection_data.hpp"

namespace MeowEngine::Runtime {
    struct ImGuiUISystem {
        ImGuiUISystem(SDL_Window* window, SDL_GLContext& context);
        ~ImGuiUISystem();

        void Input(const SDL_Event& event);
        void Render(entt::registry& registry, std::queue<std::shared_ptr<MeowEngine::ReflectionPropertyChange>>& inUIInputQueue, MeowEngine::SelectionData& pSelection, unsigned int frameBufferId, const double fps);

        // Closes any child processes like tracy
        void ClosePIDs();

//        bool IsSceneViewportFocused() const;
//        const WindowSize& GetSceneViewportSize() const;

    private:
        void OpenTracyProfiler();

        void CreateNewFrame();
        void DrawFrame(entt::registry& registry, std::queue<std::shared_ptr<MeowEngine::ReflectionPropertyChange>>& inUIInputQueue, MeowEngine::SelectionData& pSelection, uint32_t frameBufferId, const double fps);
        void RenderFrame();

        void CreateDockingSpace();

//        void CreateRender3DPanel(unsigned int frameBufferId);
//        bool isSceneViewportFocused; // soon come up with good naming conventions
//        WindowSize SceneViewportSize;

//        void CreateLifeObjectSelectorPanel(MeowEngine::Scene& scene);
//        void CreateSelectableItem(bool isEnd);
//        const ImGuiTreeNodeFlags SelectableFlags;

//        void CreateObjectEditorPanel(const core::LifeObject& selectedLifeObject);

//        void CreateLogPanel();

        bool IsRendering;

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

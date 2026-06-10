//
// Created by Akira Mujawar on 13/07/24.
//

#include "ImguiWorldTreePanel.hpp"

//#include <SDL_video.h>
//#include <SDL_events.h>
//
//#include <sys/wait.h> // For waitpid()
//#include <unistd.h> // For fork(), exec()
//#include <csignal> // For signal handling
//
#include <log.hpp>
#include "info_component.hpp"
// #include <GameplaySystem.hpp>
// #include <World.hpp>
//#include "imgui_renderer.hpp"
//#include "bridge_wrapper.hpp"

#include <RenderContext.hpp>
#include <RenderUIData.hpp>
#include <GameplaySystem.hpp>

namespace MeowEngine::Editor {

    ImGuiWorldTreePanel::ImGuiWorldTreePanel()
        : DefaultSelectableFlags(ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth)
        , DefaultSelectableNoListFlags(DefaultSelectableFlags | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen)
        , IsActive(true)
        , WindowFlags(ImGuiWindowFlags_NoCollapse) {}

    ImGuiWorldTreePanel::~ImGuiWorldTreePanel() {}

    void ImGuiWorldTreePanel::Init(Runtime::GameplaySystem& gameplay) {
        Gameplay = &gameplay;
    }

    void ImGuiWorldTreePanel::Draw(Rendering::RenderContext& renderContext, Editor::Selector &pSelection) {
        ImGui::SetNextWindowSize(ImVec2(430, 450), ImGuiCond_FirstUseEver);

        ImGui::Begin("World Tree", &IsActive); {
            for (auto& data : renderContext.UIData->RootEntities) {
                DrawHierarchy(data, renderContext);
            }

            ImGui::End();
        }
    }

    void ImGuiWorldTreePanel::DrawHierarchy(uint32_t guid, Rendering::RenderContext& renderContext) {
        auto& hierarchy = renderContext.UIData->EntityHierarchyMap[guid];

        // show drop arrow if child exists
        ImGuiTreeNodeFlags flags = hierarchy.Childs.empty() ? DefaultSelectableNoListFlags : DefaultSelectableFlags;
        flags |= ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanFullWidth;

        // if the item is selected we add selected flag?
        if (false) { // TODO:
            flags |= ImGuiTreeNodeFlags_Selected;
        }

        // draw the item and its child is existing
        bool isOpen = ImGui::TreeNodeEx(
            (void *) (intptr_t) hierarchy.GUID,
            flags,
            "%s",
            hierarchy.Name.CStr()
        );

        // we make sure the parent is expanded and actually has child
        if (isOpen && !hierarchy.Childs.empty()) {
            // expand the children
            for (auto& child : hierarchy.Childs) {
                DrawHierarchy(child, renderContext);
            }

            // all childs are tracked, we can step out of tree node
            ImGui::TreePop();
        }
    }

}

//
// Created by Akira Mujawar on 13/07/24.
//

#include "ImguiWorldTreePanel.hpp"

#include <log.hpp>

#include "info_component.hpp"

#include <RenderContext.hpp>
#include <RenderUIData.hpp>

#include <GameplaySystem.hpp>
#include <CommandQueue.hpp>
#include <SelectEntityCommand.hpp>


namespace MeowEngine::Editor {

    ImGuiWorldTreePanel::ImGuiWorldTreePanel()
        : DefaultSelectableFlags(ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth)
        , DefaultSelectableNoListFlags(DefaultSelectableFlags | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen)
        , IsActive(true)
        , WindowFlags(ImGuiWindowFlags_NoCollapse) {}

    ImGuiWorldTreePanel::~ImGuiWorldTreePanel() {}

    void ImGuiWorldTreePanel::Init() {}

    void ImGuiWorldTreePanel::Draw(Rendering::RenderContext& renderContext) {
        ImGui::SetNextWindowSize(ImVec2(430, 450), ImGuiCond_FirstUseEver);

        ImGui::Begin("World Tree", &IsActive); {
            for (auto it = renderContext.UIData->RootEntities.rbegin(); it != renderContext.UIData->RootEntities.rend(); ++it) {
                DrawHierarchy(*it, renderContext);
            }

            ImGui::End();
        }
    }

    void ImGuiWorldTreePanel::DrawHierarchy(uint32_t guid, Rendering::RenderContext& renderContext) {
        PT_PROFILE_SCOPE;

        auto& hierarchy = renderContext.UIData->EntityHierarchyMap[guid];

        // show drop arrow if child exists
        ImGuiTreeNodeFlags flags = hierarchy.Childs.empty() ? DefaultSelectableNoListFlags : DefaultSelectableFlags;
        flags |= ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanFullWidth;


        // if the item is selected we add selected flag?
        if (renderContext.UIData->SelectedEntities.find(guid) != renderContext.UIData->SelectedEntities.end()) { // TODO:
            flags |= ImGuiTreeNodeFlags_Selected;
        }

        // draw the item and its child is existing
        bool isOpen = ImGui::TreeNodeEx(
            (void *) (intptr_t) hierarchy.GUID,
            flags,
            "%s",
            hierarchy.Name.CStr()
        );

        if (ImGui::IsItemClicked()) {
            if (ImGui::GetIO().KeyCtrl) {
                renderContext.CommandQueue->Push(
                    std::make_unique<Messaging::SelectEntityCommand>(guid, true)
                );
            }
            else {
                renderContext.CommandQueue->Push(
                    std::make_unique<Messaging::SelectEntityCommand>(guid, false)
                );
            }
        }

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

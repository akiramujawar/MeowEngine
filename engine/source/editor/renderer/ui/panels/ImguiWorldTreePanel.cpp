//
// Created by Akira Mujawar on 13/07/24.
//

#include "ImguiWorldTreePanel.hpp"

#include <log.hpp>

#include "InfoComponent.hpp"

#include <RenderContext.hpp>
#include <RenderUIData.hpp>

#include <GameplaySystem.hpp>
#include <CommandQueue.hpp>
#include <imgui_internal.h>
#include <SelectEntityCommand.hpp>
#include "AddEntityCommand.hpp"
#include "RemoveEntityCommand.hpp"
#include "ImguiAssetDragDrop.hpp"
#include "ChangeEntityHierarchy.hpp"


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
            AddEntityButton(renderContext);

            ImGui::Spacing();

            for (auto it = renderContext.UIData->RootEntities.rbegin(); it != renderContext.UIData->RootEntities.rend(); ++it) {
                DragAndDropOutside(renderContext, *it);
                DrawHierarchy(renderContext, *it);
            }

            // DrawDragAndDropLine();

            ShowEntityEditMenuPopup(renderContext);

            ImGui::End();
        }
    }

    void ImGuiWorldTreePanel::AddEntityButton(Rendering::RenderContext& renderContext) {
        float headerHeight = ImGui::GetTextLineHeightWithSpacing() * 1.2f;
        const std::string& addEntityText = "Add Entity + ";
        const ImVec2 createButtonSize(ImGui::CalcTextSize(addEntityText.c_str()).x, headerHeight);
        if (ImGui::Button(addEntityText.c_str(), createButtonSize)) {
            renderContext.CommandQueue->Push(
                Messaging::ThreadType::MAIN,
                std::make_unique<Messaging::AddEntityCommand>()
            );
        }
    }

    void ImGuiWorldTreePanel::DrawHierarchy(Rendering::RenderContext& renderContext, Runtime::EntityHandle handle) {
        PT_PROFILE_SCOPE;

        auto& hierarchy = renderContext.UIData->EntityHierarchyMap[handle];

        // show drop arrow if child exists
        ImGuiTreeNodeFlags flags = hierarchy.Childs.empty() ? DefaultSelectableNoListFlags : DefaultSelectableFlags;
        flags |= ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanFullWidth;


        // if the item is selected we add selected flag?
        if (renderContext.UIData->SelectedEntities.find(handle) != renderContext.UIData->SelectedEntities.end()) { // TODO:
            flags |= ImGuiTreeNodeFlags_Selected;
        }

        // draw the item and its child is existing
        bool isOpen = ImGui::TreeNodeEx(
            (void *) (intptr_t) hierarchy.Handle.GetGUIDInt(),
            flags,
            "%s",
            hierarchy.Name.CStr()
        );

        if (ImGui::IsItemClicked()) {
            if (ImGui::GetIO().KeyCtrl) {
                renderContext.CommandQueue->Push(
                    Messaging::ThreadType::MAIN,
                    std::make_unique<Messaging::SelectEntityCommand>(handle, true)
                );
            }
            else {
                renderContext.CommandQueue->Push(
                    Messaging::ThreadType::MAIN,
                    std::make_unique<Messaging::SelectEntityCommand>(handle, false)
                );
            }
        }

        if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
            ImGui::OpenPopup("ShowEntityEditMenuPopup");
        }

        // enable drag entity
        ImguiAssetDragDrop::DragEntity(handle);
        Runtime::EntityHandle droppedHandle;

        // drag n drop entity to move into hierarchy
        if (ImguiAssetDragDrop::DropEntity(droppedHandle)) {
            renderContext.CommandQueue->Push(
                Messaging::ThreadType::MAIN,
                std::make_unique<Messaging::ChangeEntityHierarchy>(droppedHandle, handle)
            );
        }

        // we make sure the parent is expanded and actually has child
        if (isOpen && !hierarchy.Childs.empty()) {
            // expand the children
            for (auto& child : hierarchy.Childs) {
                // DrawDragAndDropLine();
                DrawHierarchy(renderContext, child);
            }

            // all childs are tracked, we can step out of tree node
            ImGui::TreePop();
        }
    }

    void ImGuiWorldTreePanel::ShowEntityEditMenuPopup(Rendering::RenderContext& renderContext) {
        if (ImGui::BeginPopup("ShowEntityEditMenuPopup")) {

            // remove all selected entities
            if(ImGui::MenuItem("Remove")) {
                for (auto& handle : renderContext.UIData->SelectedEntities) {
                    renderContext.CommandQueue->Push(
                        Messaging::ThreadType::MAIN,
                        std::make_unique<Messaging::RemoveEntityCommand>(handle)
                    );
                }
            }

            ImGui::EndPopup();
        }
    }

    void ImGuiWorldTreePanel::DragAndDropOutside(Rendering::RenderContext& renderContext, Runtime::EntityHandle handle) {
        auto size = ImGui::GetContentRegionAvail();
        size.y = 3;
        auto position = ImGui::GetCursorScreenPos();
        auto padding = 15;

        ImGui::InvisibleButton("##", size);
        if(ImGui::IsDragDropActive()) {
            auto draw = ImGui::GetWindowDrawList();

            draw->AddLine(
                ImVec2(position.x + padding, position.y),
                ImVec2(position.x + size.x - padding, position.y + size.y),
                IM_COL32(80,150,255,255),
                2.0f);
        }

        Runtime::EntityHandle droppedEntity;

        // drag n drop entity to move into hierarchy
        if (ImguiAssetDragDrop::DropEntity(droppedEntity)) {
            renderContext.CommandQueue->Push(
                Messaging::ThreadType::MAIN,
                std::make_unique<Messaging::ChangeEntityHierarchy>(droppedEntity, Runtime::EntityHandle::Invalid())
            );
        }
    }
}

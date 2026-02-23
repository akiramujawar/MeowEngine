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
//#include "imgui_renderer.hpp"
//#include "bridge_wrapper.hpp"


namespace MeowEngine::Runtime {

    ImGuiWorldTreePanel::ImGuiWorldTreePanel()
        : DefaultSelectableFlags(ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth)
        , DefaultSelectableNoListFlags(DefaultSelectableFlags | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen)
        , IsActive(true)
        , WindowFlags(ImGuiWindowFlags_NoCollapse) {}

    ImGuiWorldTreePanel::~ImGuiWorldTreePanel() {}

    void ImGuiWorldTreePanel::Draw(entt::registry &registry, MeowEngine::SelectionData &pSelection) {
        ImGui::SetNextWindowSize(ImVec2(430, 450), ImGuiCond_FirstUseEver);

        ImGui::Begin("World Tree", &IsActive); {
            auto view = registry.view<component::HierarchyComponent>();
            bool isItemClicked = false;

            for (auto entity: view) {
                // we select only the root entities
                auto component = view.get<component::HierarchyComponent>(entity);

                if (!registry.valid(component.Parent)) {
                    CreateSelectableItem(registry, pSelection, component, isItemClicked);
                }
            }

            ImGui::End();
        }

    }

    void ImGuiWorldTreePanel::CreateSelectableItem(entt::registry& registry,
                                                   MeowEngine::SelectionData& pSelection,
                                                   component::HierarchyComponent& pHierarchyComponent,
                                                   bool& pIsItemClicked) {
        const int id = static_cast<int>(pHierarchyComponent.Self);
        const bool isSelected = registry.valid(pSelection.SelectedEntity) && static_cast<int>(pSelection.SelectedEntity) == id;

        entity::InfoComponent& lifeObjectComponent = registry.get<entity::InfoComponent>(pHierarchyComponent.Self);
        bool hasChild = registry.valid(pHierarchyComponent.FirstChild);
        // hs a hierarchy?
        ImGuiTreeNodeFlags flags = !hasChild ? DefaultSelectableNoListFlags : DefaultSelectableFlags;
        flags |= ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanFullWidth;

        // if the item is selected we add selected flag?
        if (isSelected) {
            flags |= ImGuiTreeNodeFlags_Selected;
        }

        // draw the item and its child is exists
        bool isOpen = ImGui::TreeNodeEx(
            (void *) (intptr_t) id,
            flags,
            "%s",
            lifeObjectComponent.Name.c_str()
        );


        // if item gets clicked with cache item
        if (!pIsItemClicked && ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen()) {
            MeowEngine::Log("Object Selected: ", std::to_string(id));
            pSelection.SelectedEntity = pHierarchyComponent.Self;

            pIsItemClicked = true;
        }

        if(hasChild && isOpen){
            // show the child items in hierarchy
            if(registry.valid(pHierarchyComponent.FirstChild)) {
                CreateSelectableItem(registry, pSelection, registry.get<component::HierarchyComponent>(pHierarchyComponent.FirstChild), pIsItemClicked);
            }

            ImGui::TreePop();
        }

        // show the next item in hierarchy (sibling of current item)
        if(registry.valid(pHierarchyComponent.Next)) {
            CreateSelectableItem(registry, pSelection, registry.get<component::HierarchyComponent>(pHierarchyComponent.Next), pIsItemClicked);
        }
    }
}

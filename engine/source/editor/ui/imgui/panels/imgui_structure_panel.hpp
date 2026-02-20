//
// Created by Akira Mujawar on 13/07/24.
//

#ifndef MEOWENGINE_IMGUI_STRUCTURE_PANEL_HPP
#define MEOWENGINE_IMGUI_STRUCTURE_PANEL_HPP

//#include <scene.hpp>
//#include "opengl_framebuffer.hpp"
//#include "window_size.hpp"
#include "imgui_wrapper.hpp"
#include "entt_wrapper.hpp"

#include "hierarchy_component.hpp"
#include "selection_data.hpp"

namespace MeowEngine::graphics::ui {
    struct ImGuiStructurePanel {
        ImGuiStructurePanel();
        ~ImGuiStructurePanel();

        void Draw(entt::registry& registry, MeowEngine::SelectionData& pSelection);
        void CreateSelectableItem(
                entt::registry& registry,
                MeowEngine::SelectionData& pSelection,
                component::HierarchyComponent& pHierarchyComponent,
                bool& pIsItemClicked);

    private:
        const ImGuiTreeNodeFlags DefaultSelectableFlags;
        const ImGuiTreeNodeFlags DefaultSelectableNoListFlags;
        int SelectionMask; // TODO: try to understand the logic

        bool IsActive;
        ImGuiWindowFlags WindowFlags;
    };
}


#endif //MEOWENGINE_IMGUI_STRUCTURE_PANEL_HPP

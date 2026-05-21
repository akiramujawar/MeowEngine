//
// Created by Akira Mujawar on 13/07/24.
//

#ifndef MEOWENGINE_IMGUIWORLDTREEPANEL_HPP
#define MEOWENGINE_IMGUIWORLDTREEPANEL_HPP

//#include <scene.hpp>
//#include "opengl_framebuffer.hpp"
//#include "window_size.hpp"
#include "ImguiAPI.hpp"
#include "entt.hpp"

#include "hierarchy_component.hpp"
#include "Selector.hpp"

namespace MeowEngine::Runtime {
    class GameplaySystem;
}


namespace MeowEngine::Editor {
    struct ImGuiWorldTreePanel {
        ImGuiWorldTreePanel();
        ~ImGuiWorldTreePanel();

        void Init(Runtime::GameplaySystem& gameplay);
        void Draw(entt::registry& registry, Editor::Selector& pSelection);
        void CreateSelectableItem(
                entt::registry& registry,
                Editor::Selector& pSelection,
                component::HierarchyComponent& pHierarchyComponent,
                bool& pIsItemClicked);

    private:
        const ImGuiTreeNodeFlags DefaultSelectableFlags;
        const ImGuiTreeNodeFlags DefaultSelectableNoListFlags;
        int SelectionMask; // TODO: try to understand the logic

        bool IsActive;
        ImGuiWindowFlags WindowFlags;

        Runtime::GameplaySystem* Gameplay;
    };
}


#endif //MEOWENGINE_IMGUIWORLDTREEPANEL_HPP

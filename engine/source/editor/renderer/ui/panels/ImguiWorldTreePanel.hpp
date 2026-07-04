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

#include "HierarchyComponent.hpp"
#include "Selector.hpp"
#include "EntityID.hpp"

namespace MeowEngine::Runtime {
    class GameplaySystem;
}

namespace MeowEngine::Rendering {
    struct RenderContext;
}

namespace MeowEngine::Editor {
    struct ImGuiWorldTreePanel {
        ImGuiWorldTreePanel();
        ~ImGuiWorldTreePanel();

        void Init();
        void Draw(Rendering::RenderContext& renderContext);

    private:
        void AddEntityButton(Rendering::RenderContext& renderContext);
        void DrawHierarchy(Rendering::RenderContext& renderContext, Runtime::EntityHandle handle);
        void ShowEntityEditMenuPopup(Rendering::RenderContext& renderContext);
        void DragAndDropOutside(Rendering::RenderContext& renderContext, Runtime::EntityHandle handle);

    private:
        const ImGuiTreeNodeFlags DefaultSelectableFlags;
        const ImGuiTreeNodeFlags DefaultSelectableNoListFlags;
        int SelectionMask; // TODO: try to understand the logic

        bool IsActive;
        ImGuiWindowFlags WindowFlags;
    };
}


#endif //MEOWENGINE_IMGUIWORLDTREEPANEL_HPP

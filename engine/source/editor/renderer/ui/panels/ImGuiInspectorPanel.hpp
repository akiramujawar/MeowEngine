//
// Created by Akira Mujawar on 13/07/24.
//

#ifndef MEOWENGINE_IMGUIINSPECTORPANEL_HPP
#define MEOWENGINE_IMGUIINSPECTORPANEL_HPP

#include "Public/Math.hpp"
#include "entt.hpp"

#include "Selector.hpp"
#include "reflection_property_change.hpp"
#include "queue"


namespace MeowEngine::Rendering {
    struct RenderContext;
}

namespace MeowEngine::Editor {
    struct ImGuiInspectorPanel {
        ImGuiInspectorPanel();
        ~ImGuiInspectorPanel();

        void Init();
        void Draw(Rendering::RenderContext& renderContext);

    private:
        void ShowAddComponentPopup(const Rendering::RenderContext& renderContext);
        void ShowComponents(const Rendering::RenderContext& renderContext);
    private:
        bool CanDrawPanel;
    };
}


#endif //MEOWENGINE_IMGUIINSPECTORPANEL_HPP

//
// Created by Akira Mujawar on 13/07/24.
//

#ifndef MEOWENGINE_IMGUIWORLDINSPECTORPANEL_HPP
#define MEOWENGINE_IMGUIWORLDINSPECTORPANEL_HPP

#include "Public/Math.hpp"
#include "entt.hpp"

#include "Selector.hpp"
#include "reflection_property_change.hpp"
#include "queue"


namespace MeowEngine::Rendering {
    struct RenderContext;
}

namespace MeowEngine::Editor {
    struct ImGuiWorldInspectorPanel {
        ImGuiWorldInspectorPanel();
        ~ImGuiWorldInspectorPanel();

        void Init();
        void Draw(Rendering::RenderContext& renderContext);

    private:
        bool CanDrawPanel;
    };
}


#endif //MEOWENGINE_IMGUIWORLDINSPECTORPANEL_HPP

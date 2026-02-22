//
// Created by Akira Mujawar on 13/07/24.
//

#ifndef MEOWENGINE_IMGUIWORLDINSPECTORPANEL_HPP
#define MEOWENGINE_IMGUIWORLDINSPECTORPANEL_HPP

#include "math_wrapper.hpp"
#include "entt_wrapper.hpp"

#include "selection_data.hpp"
#include "reflection_property_change.hpp"
#include "queue"

namespace MeowEngine::Runtime {
    struct ImGuiWorldInspectorPanel {
        ImGuiWorldInspectorPanel();
        ~ImGuiWorldInspectorPanel();

        void Draw(entt::registry& registry, std::queue<std::shared_ptr<MeowEngine::ReflectionPropertyChange>>& inUIInputQueue, MeowEngine::SelectionData& pSelection);

    private:
        bool CanDrawPanel;
    };
}


#endif //MEOWENGINE_IMGUIWORLDINSPECTORPANEL_HPP

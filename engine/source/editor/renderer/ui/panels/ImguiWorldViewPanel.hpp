//
// Created by Akira Mujawar on 14/07/24.
//

#ifndef MEOWENGINE_IMGUIWORLDVIEWPANEL_HPP
#define MEOWENGINE_IMGUIWORLDVIEWPANEL_HPP

#include "ImguiAPI.hpp"
#include "Public/Math.hpp"


namespace MeowEngine::Rendering {
    struct RenderContext;
}

namespace MeowEngine::Editor {

    struct ImGuiWorldViewPanel {
        ImGuiWorldViewPanel();
        ~ImGuiWorldViewPanel();

        void Init();
        void Draw(Rendering::RenderContext& renderContext);

    private:
        bool IsActive;
        bool IsFocused; // soon come up with good naming conventions

        ImGuiWindowFlags WindowFlags;
        Vector2Int SceneViewportSize;
    };
}


#endif //MEOWENGINE_IMGUIWORLDVIEWPANEL_HPP

//
// Created by Akira Mujawar on 14/07/24.
//

#ifndef MEOWENGINE_IMGUIDOCKERSPACE_HPP
#define MEOWENGINE_IMGUIDOCKERSPACE_HPP

#include "ImguiMainMenu.hpp"

namespace MeowEngine::Rendering {
    struct RenderContext;
}

namespace MeowEngine::Editor {
    class ImGuiDockerSpace {
    public:
        ImGuiDockerSpace();

        ~ImGuiDockerSpace();

        void SetupDockingSpace(Rendering::RenderContext& renderContext);

    private:
        bool IsFullScreen;
        int DockSpaceFlags;
        int WindowFlags;

        ImguiMainMenu MainMenu;
    };
}


#endif //MEOWENGINE_IMGUIDOCKERSPACE_HPP

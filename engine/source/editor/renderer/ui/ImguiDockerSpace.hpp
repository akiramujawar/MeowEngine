//
// Created by Akira Mujawar on 14/07/24.
//

#ifndef MEOWENGINE_IMGUIDOCKERSPACE_HPP
#define MEOWENGINE_IMGUIDOCKERSPACE_HPP

namespace MeowEngine::Editor {
    class ImGuiDockerSpace {
    public:
        ImGuiDockerSpace();

        ~ImGuiDockerSpace();

        void SetupDockingSpace();

    private:
        bool IsFullScreen;
        int DockSpaceFlags;
        int WindowFlags;
    };
}


#endif //MEOWENGINE_IMGUIDOCKERSPACE_HPP

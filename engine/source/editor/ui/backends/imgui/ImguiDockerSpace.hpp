//
// Created by Akira Mujawar on 14/07/24.
//

#ifndef MEOWENGINE_IMGUIDOCKERSPACE_HPP
#define MEOWENGINE_IMGUIDOCKERSPACE_HPP

namespace MeowEngine::Runtime {
    struct ImGuiDockerSpace {
        ImGuiDockerSpace();

        ~ImGuiDockerSpace();

    private:
        bool IsActive;
    };
}


#endif //MEOWENGINE_IMGUIDOCKERSPACE_HPP

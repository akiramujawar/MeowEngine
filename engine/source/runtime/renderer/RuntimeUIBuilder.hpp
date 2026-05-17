//
// Created by Akira Mujawar on 17/05/26.
//

#ifndef MEOWENGINE_IMGUIUISYSTEM_HPP
#define MEOWENGINE_IMGUIUISYSTEM_HPP

namespace MeowEngine::Runtime {
    /**
     * Screen space UI (tied to imgui) like buttons, panels, runtime debug, etc...
     */
    class RuntimeUIBuilder {
        public:
        RuntimeUIBuilder();
        ~RuntimeUIBuilder();

        void Init();
        void Input();
        void BuildDrawData();
    };
}


#endif //MEOWENGINE_IMGUIUISYSTEM_HPP
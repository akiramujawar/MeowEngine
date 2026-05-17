//
// Created by Akira Mujawar on 14/05/26.
//

#ifndef MEOWENGINE_EDITORMODULE_HPP
#define MEOWENGINE_EDITORMODULE_HPP

#include <Public/Threading/Include.hpp>

#include <entt_single_buffer.hpp>
#include <Selector.hpp>


namespace MeowEngine::Editor {
    /**
     * Owns the editor states, features & coordinates internally
     * NOTE: Similar can be created for runtime & thus expanding for external module
     */
    class EditorModule {
    public:
        EditorModule();
        ~EditorModule();

        void Init();
        void Schedule(Threading::Scheduler& scheduler);

        Selector& GetSelector();
        EnttBufferBase& GetInputBuffer();

    private:
        Selector Selector;

        /**
         * This gives double buffering & reflection for ui inputs
         * NOTE: this needs to be decoupled and removed
         */
        EnttSingleBuffer EnttSingleBuffer;
    };
}


#endif //MEOWENGINE_EDITORMODULE_HPP
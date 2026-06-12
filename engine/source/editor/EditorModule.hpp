//
// Created by Akira Mujawar on 14/05/26.
//

#ifndef MEOWENGINE_EDITORMODULE_HPP
#define MEOWENGINE_EDITORMODULE_HPP

#include <Public/Threading/Include.hpp>

// #include <entt_single_buffer.hpp>
#include <Selector.hpp>
#include <FileDialog.hpp>

namespace MeowEngine::Editor {
    struct EditorInitContext;

    /**
     * Owns the editor states, features & coordinates internally
     * NOTE: Similar can be created for runtime & thus expanding for external module
     */
    class EditorModule {
    public:
        EditorModule();
        ~EditorModule();

        void Init(EditorInitContext& context);
        void Schedule(Threading::Scheduler& scheduler);

        Selector& GetSelector() {
            return Selector;
        }

        FileDialog& GetFileDialog() {
            return FileDialog;
        }

        // EnttBufferBase& GetInputBuffer();

    private:
        Selector Selector;
        FileDialog FileDialog;

        // /**
        //  * This gives double buffering & reflection for ui inputs
        //  * NOTE: this needs to be decoupled and removed
        //  */
        // EnttSingleBuffer EnttSingleBuffer;
    };
}


#endif //MEOWENGINE_EDITORMODULE_HPP
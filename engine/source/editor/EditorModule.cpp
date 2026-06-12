//
// Created by Akira Mujawar on 14/05/26.
//

#include "EditorModule.hpp"

#include <Public/MeowEngine.hpp>

namespace MeowEngine::Editor {

    EditorModule::EditorModule() {
        MeowEngine::Log("EditorModule", "Constructed");
    }

    EditorModule::~EditorModule() {
        MeowEngine::Log("EditorModule", "Destructed");
    }

    void EditorModule::Init(EditorInitContext& context) {
        Selector.Init(Runtime::GetProject().ProjectSettings.GetProjectPath());
        FileOpener.Init(context);
    }

    void EditorModule::Schedule(Threading::Scheduler& scheduler) {

    }

    // EnttBufferBase& EditorModule::GetInputBuffer() { return EnttSingleBuffer; }
}

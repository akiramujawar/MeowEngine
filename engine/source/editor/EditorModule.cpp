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

    void EditorModule::Init() {
        Selector.Init(Runtime::GetProject().ProjectSettings.GetProjectPath());
    }

    void EditorModule::Schedule(Threading::Scheduler& scheduler) {}

    Selector& EditorModule::GetSelector() { return Selector; }

    EnttBufferBase& EditorModule::GetInputBuffer() { return EnttSingleBuffer; }
}

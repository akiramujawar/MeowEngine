//
// Created by Akira Mujawar on 14/05/26.
//

#include <EditorModule.hpp>

#include <EditorInitContext.hpp>
#include <Project.hpp>

namespace MeowEngine::Editor {

    EditorModule::EditorModule() {
        MeowEngine::Log("EditorModule", "Constructed");
    }

    EditorModule::~EditorModule() {
        MeowEngine::Log("EditorModule", "Destructed");
    }

    void EditorModule::Init(EditorInitContext& context) {
        context.Project->Settings.InitDevelopment();

        Selector.Init(context.Project->Settings.GetProjectPath());
        FileDialog.Init(context);
    }

    void EditorModule::Schedule(Threading::Scheduler& scheduler) {

    }

    // EnttBufferBase& EditorModule::GetInputBuffer() { return EnttSingleBuffer; }
}

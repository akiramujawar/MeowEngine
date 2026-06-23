//
// Created by Akira Mujawar on 14/05/26.
//

#include <EditorModule.hpp>

#include <EditorInitData.hpp>
#include <ConfigManager.hpp>

namespace MeowEngine::Editor {

    EditorModule::EditorModule() {
        MeowEngine::Log("EditorModule", "Constructed");
    }

    EditorModule::~EditorModule() {
        MeowEngine::Log("EditorModule", "Destructed");
    }

    void EditorModule::Init(EditorInitData& context) {
        // context.Project->Paths.InitDevelopment();

        Selector.Init(context.Project->Paths.GetSandboxRootPath());
        FileDialog.Init(context);
    }

    void EditorModule::Schedule(Threading::Scheduler& scheduler) {

    }

    // EnttBufferBase& EditorModule::GetInputBuffer() { return EnttSingleBuffer; }
}

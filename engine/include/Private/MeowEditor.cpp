//
// Created by Akira Mujawar on 14/05/26.
//

#include <Public/MeowEditor.hpp>

#include <Engine.hpp>
// #include <AssetManager.hpp>
// #include <Project.hpp>

namespace MeowEngine::Editor {
    EditorModule& GetEditor() {
        return Engine::Get().GetEditorModule();
    }
}
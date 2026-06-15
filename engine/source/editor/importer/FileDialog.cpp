//
// Created by Akira Mujawar on 12/06/26.
//

#include <FileDialog.hpp>

#include <SDL_NativeFileDialog.hpp>
#include <EditorInitData.hpp>
#include <GraphicsDevice.hpp>

namespace MeowEngine::Editor {
    FileDialog::FileDialog() {
        Platform::SDL_NativeFileDialog::Init();
    }

    FileDialog::~FileDialog() {
        Platform::SDL_NativeFileDialog::Quit();
    }

    void FileDialog::Init(const EditorInitData& context) {
        Window = &context.GraphicsDevice->GetWindow();
    }

    void FileDialog::ShowPickFolderPopup(std::string& selectedDirectory) const {
        Platform::SDL_NativeFileDialog::PickFolder(Window->GetHandle(), selectedDirectory);
    }

    void FileDialog::ShowImportPopup(std::string& selectedFile) const {
        Platform::SDL_NativeFileDialog::OpenDialog(Window->GetHandle(), selectedFile);
    }

    void FileDialog::ShowImportPopup(std::vector<std::string>& selectedFiles) const {
        Platform::SDL_NativeFileDialog::OpenDialogMultiple(Window->GetHandle(), selectedFiles);
    }
}

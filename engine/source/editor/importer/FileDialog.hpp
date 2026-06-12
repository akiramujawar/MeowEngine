//
// Created by Akira Mujawar on 12/06/26.
//

#ifndef MEOWENGINE_FILEDIALOG_HPP
#define MEOWENGINE_FILEDIALOG_HPP

#include <string>
#include <vector>

namespace MeowEngine::Platform {
    class SDL_EngineWindow;
}

namespace MeowEngine::Editor {
    struct EditorInitContext;

    class FileDialog {
    public:
        FileDialog();
        ~FileDialog();

        void Init(const EditorInitContext& context);

        void ShowPickFolderPopup(std::string& selectedDirectory) const;
        void ShowImportPopup(std::string& selectedFile) const;
        void ShowImportPopup(std::vector<std::string>& selectedFiles) const;

    private:
        Platform::SDL_EngineWindow* Window = nullptr;
    };
}

// open project code through Engine.cmake - cpp & hpp files
// open project code through cmake-post-build - shaders, objs, textures

#endif //MEOWENGINE_FILEDIALOG_HPP
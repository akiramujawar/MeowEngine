//
// Created by Akira Mujawar on 12/06/26.
//

#include <ImportFileCommand.hpp>

#include <AssetImporter.hpp>
#include <MessageContext.hpp>
#include <FileDialog.hpp>

namespace MeowEngine::Messaging {

    void ImportFileCommand::Execute(MessageContext& context) {
        std::vector<std::string> selectedFiles;
        context.FileDialog->ShowImportPopup(selectedFiles);

        for (auto& importFilePath : selectedFiles) {
            Editor::AssetImporter::Import(importFilePath, ImportFolderPath);
        }
    }

}

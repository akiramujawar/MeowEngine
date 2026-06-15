//
// Created by Akira Mujawar on 12/06/26.
//

#include <ImportFileCommand.hpp>

#include <AssetSerializer.hpp>
#include <MessageInitData.hpp>
#include <FileDialog.hpp>

namespace MeowEngine::Messaging {

    void ImportFileCommand::Execute(MessageInitData& context) {
        std::vector<std::string> selectedFiles;
        context.FileDialog->ShowImportPopup(selectedFiles);

        // TODO: read extension and accordingly perform the action
        // here we might involve different types of importers like png, jpegs and soo on...
        for (auto& importFilePath : selectedFiles) {
            Asset::AssetSerializer::Serialize(importFilePath, ImportFolderPath);
        }
    }

}

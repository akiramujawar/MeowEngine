//
// Created by Akira Mujawar on 12/06/26.
//

#include <ImportFileCommand.hpp>

#include "Public/Core/Include.hpp"
#include <AssetSerializer.hpp>
#include <MessageInitData.hpp>
#include <FileDialog.hpp>

#include "MeshImporter.hpp"
#include "TextureImporter.hpp"

namespace MeowEngine::Messaging {

    void ImportFileCommand::Execute(MessageInitData& context) {
        std::vector<std::string> selectedFiles;
        // TODO: add filters
        context.FileDialog->ShowImportPopup(selectedFiles);

        for (auto& importFilePath : selectedFiles) {
            switch (Type) {
                case Asset::AssetImportType::NONE:
                    break;
                case Asset::AssetImportType::MESH:
                    Asset::MeshImporter::Import(Path(importFilePath), Path(ImportToFolderPath));
                    break;
                case Asset::AssetImportType::TEXTURE:
                    Asset::TextureImporter::Import(Path(importFilePath), Path(ImportToFolderPath));
                    break;
                case Asset::AssetImportType::WORLD:
                    break;
            }
        }

    }

}

//
// Created by Akira Mujawar on 15/06/26.
//

#include "TextureAssetImporter.hpp"

#include "log.hpp"
#include "Public/IO/Include.hpp"
#include "AssetSerializer.hpp"
#include "AssetManager.hpp"
#include "TextureSerializer.hpp"


namespace MeowEngine::Asset {

    void TextureAssetImporter::Import(const Path& filePath, const Path& importToFolderPath) {
        MeowEngine::Log("Shader Import", {filePath.GetRawString(), importToFolderPath.GetRawString()});

        auto exportPath = importToFolderPath + filePath.GetName();
        exportPath.ReplaceExtension(".meowdata");

        if (!filePath.Exists() || !importToFolderPath.Exists()) {
            MeowEngine::Log("MeshAssetImporter", "Error");
            return;
        }

        { // create empty file if doesn't exist
            const auto serializer = AssetSerializer::OpenSerializer(exportPath, FileSystem::FileMode::READ);
            AssetHeader header;
            if (!AssetSerializer::ReadHeader(serializer, header)) {
                AssetManager::CreateAndSaveEmptyAsset(AssetHandle::CreateTemp(), AssetType::TEXTURE, exportPath);
            }
        }

        const std::vector<uint8_t> assetData = FileSystem::File::ReadAll(filePath.GetRawString());
        TextureSerializer::Serialize(exportPath, assetData);
    }

}

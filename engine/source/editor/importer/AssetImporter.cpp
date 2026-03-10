//
// Created by Akira Mujawar on 05/03/26.
//

#include <AssetImporter.hpp>
#include <AssetHeader.hpp>
#include <AssetType.hpp>

#include <IO.hpp>

using namespace MeowEngine::Runtime;

namespace {
    Asset::AssetType GetAssetType(const std::string& extension) {
        if (extension == ".png" || extension == ".jpg") {
            return Asset::AssetType::TEXTURE;
        }

        if (extension == ".obj") {
            return Asset::AssetType::MESH;
        }

        return Asset::AssetType::UNKNOWN;
    }

    void ImportTextureSetting(std::string& setting) {
        setting = "{}";
    }

    void ImportMeshSetting(std::string& setting) {
        setting = "{}";
    }

    std::string GetSettings(const Asset::AssetType& type) {
        std::string setting;

        switch (type) {
            case Asset::AssetType::TEXTURE:
                ImportTextureSetting(setting);
                break;
            case Asset::AssetType::MESH:
                ImportMeshSetting(setting);
                break;
            case Asset::AssetType::WORLD:
                break;
            case Asset::AssetType::MATERIAL:
                break;
            default:
                break;
        }

        return setting;
    }
}

namespace MeowEngine::Editor {

    void AssetImporter::Import(const std::string_view& importPath, const std::string_view& savePath) {
        const FileSystem::Path importFilePath(importPath);
        const Asset::AssetType type = GetAssetType(importFilePath.GetExtension().GetRawString());

        // only copy-paste
        if (type == Asset::AssetType::UNKNOWN) {
            FileSystem::FileSystem::Move(importFilePath, savePath);
            return;
        }

        // path to selected asset directory with new extension
        FileSystem::Path saveFilePath = FileSystem::Path(savePath) + importFilePath.GetName();
        saveFilePath.ReplaceExtension("meowdata");

        const uint32_t uuid = 999;
        const std::string setting = GetSettings(type);
        const std::vector<uint8_t> assetData = FileSystem::File::ReadAll(importPath);

        // set the header for the file
        Asset::AssetHeader header {uuid, static_cast<int>(type)};
        header.SettingIndicator = sizeof(Asset::AssetHeader);
        header.SettingSize = setting.size();
        header.DataIndicator = header.SettingIndicator + header.SettingSize;
        header.DataSize = assetData.size();

        // save to disk
        FileSystem::FileStream stream;
        stream.Open(saveFilePath, FileSystem::FileMode::WRITE);

        stream.Write(&header, sizeof(Asset::AssetHeader));
        stream.Write(setting.data(), header.SettingSize);
        stream.Write(assetData.data(), header.DataSize);

        stream.Flush();
        stream.Close();
    }

}

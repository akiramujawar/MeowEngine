//
// Created by Akira Mujawar on 05/03/26.
//

#include <AssetSerializer.hpp>
#include <AssetHeader.hpp>
#include <AssetType.hpp>
#include <AssetMetadata.hpp>

#include <Public/IO.hpp>
#include <MeowService.hpp>
#include <UUID.hpp>

#include <AssetManager.hpp>
#include <AssetRegistrySerializer.hpp>
#include <Project.hpp>


namespace {
    MeowEngine::Asset::AssetType GetAssetType(const std::string& extension) {
        if (extension == ".png" || extension == ".jpg") {
            return MeowEngine::Asset::AssetType::TEXTURE;
        }

        if (extension == ".obj") {
            return MeowEngine::Asset::AssetType::MESH;
        }

        return MeowEngine::Asset::AssetType::UNKNOWN;
    }

    void ImportTextureSetting(std::string& setting) {
        setting = "{}";
    }

    void ImportMeshSetting(std::string& setting) {
        setting = "{}";
    }

    std::string GetSettings(const MeowEngine::Asset::AssetType& type) {
        std::string setting;

        switch (type) {
            case MeowEngine::Asset::AssetType::TEXTURE:
                ImportTextureSetting(setting);
                break;
            case MeowEngine::Asset::AssetType::MESH:
                ImportMeshSetting(setting);
                break;
            case MeowEngine::Asset::AssetType::WORLD:
                break;
            case MeowEngine::Asset::AssetType::MATERIAL:
                break;
            default:
                break;
        }

        return setting;
    }
}

namespace MeowEngine::Asset {
    Serialization::Serializer AssetSerializer::OpenSerializer(Path path, const FileSystem::FileMode mode) {
        Path fileName = path.GetName();

        std::shared_ptr<FileSystem::FileStream> stream = std::make_shared<FileSystem::FileStream>();
        stream->Open(path.GetRawString().data(), mode);

        const Serialization::Serializer serializer {fileName, path, stream};

        return serializer;
    }

    void AssetSerializer::CloseSerializer(const Serialization::Serializer& serializer) {
        auto& stream = serializer.GetStream();
        stream.Close();
    }

    bool AssetSerializer::ReadHeader(const Serialization::Serializer& serializer, AssetHeader& header) {
        auto& stream = serializer.GetStream();
        stream.Read(&header, sizeof(Asset::AssetHeader));

        // check for file validity
        if (strncmp(header.Magic, "MEOW", 4) != 0) {
            // std::string logMessage = "Invalid Asset: " + stream.GetPath();
            // MeowEngine::Log("Asset Serializer", logMessage, LogType::ERROR);

            return false;
        }

        return true;
    }

    void AssetSerializer::WriteHeader(const Serialization::Serializer& serializer, const AssetHeader& header) {
        auto& stream = serializer.GetStream();
        stream.Write(&header, sizeof(Asset::AssetHeader));

        // serializer.Write<AssetHeader>(header);
    }

    void AssetSerializer::ReadMetadata(const Serialization::Serializer& serializer, AssetMetadata& metadata) {
        metadata.Type = static_cast<AssetType>(serializer.ReadInt());
        metadata.Path = serializer.ReadString();
        metadata.Handle = AssetHandle::Create(serializer.ReadUInt64());
    }

    void AssetSerializer::WriteMetadata(const Serialization::Serializer& serializer, const AssetMetadata& metadata) {
        serializer.WriteInt(static_cast<int>(metadata.Type));
        serializer.WriteString(metadata.Path);
        serializer.WriteUInt64(metadata.Handle.GetUUID());
    }

    bool AssetSerializer::CreateEmptyMeowdata(const Path& path, const AssetHeader& header) {
        MeowEngine::Log("AssetSerializer", {"Creating empty asset", path.GetRawString()});
        auto serializer = OpenSerializer(path, FileSystem::FileMode::WRITE);

        WriteHeader(serializer, header);
        serializer.WriteUInt32(0);

        CloseSerializer(serializer);

        return true;
    }


    void AssetSerializer::Serialize(const std::string_view& importPath, const std::string_view& savePath) {
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

        const uint64_t uuid = Core::UUID::GenerateUUID();
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

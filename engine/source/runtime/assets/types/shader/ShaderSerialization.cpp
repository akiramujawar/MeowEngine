//
// Created by Akira Mujawar on 25/06/26.
//

#include "ShaderSerialization.hpp"

#include "log.hpp"
#include "Public/IO/Include.hpp"
#include "AssetSerializer.hpp"
#include "unordered_map"

namespace MeowEngine::Asset {

    bool ShaderSerialization::Serialize(const Path& path, const std::string& data, ShaderType type) {
        MeowEngine::Log("ShaderSerialization", "Serialize");

        // read existing header
        auto readSerializer = AssetSerializer::OpenSerializer(path, FileSystem::FileMode::READ);
        AssetHeader header;
        AssetSerializer::ReadHeader(readSerializer, header);

        // read existing shader data
        std::array<std::string, static_cast<int>(ShaderType::SHADER_COUNT)> shaderSources;
        while (!readSerializer.IsEnd()) {
            auto readType = readSerializer.ReadInt();
            auto readData = readSerializer.ReadString();

            shaderSources[readType] = readData;
        }

        // set our new data of passed shader type
        shaderSources[static_cast<int>(type)] = data;

        AssetSerializer::CloseSerializer(readSerializer);

        // create temp
        auto tempPath = path;
        tempPath.ReplaceExtension("meowtemp");

        auto writeSerializer = AssetSerializer::OpenSerializer(tempPath, FileSystem::FileMode::WRITE);
        AssetSerializer::WriteHeader(writeSerializer, header);

        // write all shader data
        // type, data
        for (int i = 0 ; i < shaderSources.size(); i++) {
            writeSerializer.WriteInt(i);
            writeSerializer.WriteString(shaderSources[i]);
        }

        // close & get back temp file
        AssetSerializer::CloseSerializer(writeSerializer);

        if (!FileSystem::FileSystem::Replace(path, tempPath)) {
            FileSystem::FileSystem::Remove(tempPath);

            return false;
        }

        return true;
    }

    bool ShaderSerialization::Deserialize(const Path& path, ShaderAsset& asset) {
        MeowEngine::Log("ShaderSerialization", "Deserialize");

        auto serializer = AssetSerializer::OpenSerializer(path, FileSystem::FileMode::READ);

        AssetHeader header;
        bool isValidAsset = AssetSerializer::ReadHeader(serializer, header);

        if (!isValidAsset) {
            return false;
        }

        std::array<std::string, static_cast<int>(ShaderType::SHADER_COUNT)> shaderSources;

        for (int i = 0 ; i < shaderSources.size(); i++) {
            auto type = serializer.ReadInt();
            auto data = serializer.ReadString();

            asset.SetSource(static_cast<ShaderType>(type), data);
        }

        AssetSerializer::CloseSerializer(serializer);

        return true;
    }
}

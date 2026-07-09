//
// Created by Akira Mujawar on 09/07/26.
//

#include "PhysicsMaterialSerializer.hpp"

#include "Public/IO/Include.hpp"
#include "AssetSerializer.hpp"

namespace MeowEngine::Asset {
    bool PhysicsMaterialSerializer::Serialize(const Path& path, PhysicsMaterialAsset& asset) {
        MeowEngine::Log("PhysicsMaterialSerializer::Serialize", "");

        // read existing header
        auto readSerializer = AssetSerializer::OpenSerializer(path, FileSystem::FileMode::READ);
        AssetHeader header;
        AssetSerializer::ReadHeader(readSerializer, header);
        AssetSerializer::CloseSerializer(readSerializer);

        auto tempPath = path;
        tempPath.ReplaceExtension("meowtemp");

        // -------- serialization ahead
        auto writeSerializer = AssetSerializer::OpenSerializer(tempPath, FileSystem::FileMode::WRITE);
        AssetSerializer::WriteHeader(writeSerializer, header);

        writeSerializer.WriteFloat(1);
        writeSerializer.WriteFloat(1);
        writeSerializer.WriteFloat(1);

        AssetSerializer::CloseSerializer(writeSerializer);

        if (!FileSystem::FileSystem::Replace(path, tempPath)) {
            FileSystem::FileSystem::Remove(tempPath);

            return false;
        }

        return true;
    }

    bool PhysicsMaterialSerializer::Deserialize(const Path& path, PhysicsMaterialAsset& asset) {
        MeowEngine::Log("PhysicsMaterialSerializer::Deserialize", "Started");

        // --------------- serialization ahead
        auto serializer = AssetSerializer::OpenSerializer(path, FileSystem::FileMode::READ);

        AssetHeader header;
        const bool isValidAsset = AssetSerializer::ReadHeader(serializer, header);

        if (!isValidAsset) {
            return false;
        }

        asset.DynamicFriction = serializer.ReadFloat();
        asset.DynamicFriction = serializer.ReadFloat();
        asset.Restitution = serializer.ReadFloat();

        AssetSerializer::CloseSerializer(serializer);

        MeowEngine::Log("PhysicsMaterialSerializer::Deserialize", "Finished");
        return true;
    }
}

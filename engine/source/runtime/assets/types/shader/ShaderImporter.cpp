//
// Created by Akira Mujawar on 25/06/26.
//

#include "ShaderImporter.hpp"

#include "log.hpp"
#include "Public/Core/Include.hpp"
#include "Public/IO/Include.hpp"
#include "AssetManager.hpp"

#include "AssetSerializer.hpp"
#include "ShaderSerialization.hpp"
#include "ShaderType.hpp"


namespace MeowEngine::Asset {
    void ShaderImporter::Import(
        const Path& exportPath,
        const Path& vertexPath,
        const Path& fragmentPath
    ){
        MeowEngine::Log("Shader Import", {exportPath.GetRawString(), vertexPath.GetRawString(), fragmentPath.GetRawString()});

        { // create empty file if doesn't exist
            const auto serializer = AssetSerializer::OpenSerializer(exportPath, FileSystem::FileMode::READ);
            AssetHeader header;
            if (!AssetSerializer::ReadHeader(serializer, header)) {
                AssetManager::CreateAndSaveEmptyAsset(AssetHandle::CreateTemp(), AssetType::SHADER, exportPath);
            }
        }

        if (vertexPath.Exists()) {
            const auto assetData = FileSystem::File::ReadText(vertexPath.GetRawString());
            ShaderSerialization::Serialize(
                exportPath,
                assetData,
                ShaderType::VERTEX
            );
        }

        if (fragmentPath.Exists()) {
            const auto assetData = FileSystem::File::ReadText(fragmentPath.GetRawString());
            ShaderSerialization::Serialize(
                exportPath,
                assetData,
                ShaderType::FRAGMENT
            );
        }

        // shader asset required only once then shader resource\
        // mesh asset required only once then mesh resource
        // texture asset required only once then texture resource
        // save?
        // when to put in registry

        // bigger question -> does it matter at this stage? not everything as to be perfect ;)
        // only when new assets are added?
        // builder build registry will be built every run?
        // read every file build registry
    }
}

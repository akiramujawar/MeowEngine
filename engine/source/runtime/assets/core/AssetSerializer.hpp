//
// Created by Akira Mujawar on 05/03/26.
//

#ifndef MEOWENGINE_ASSETSERIALIZER_HPP
#define MEOWENGINE_ASSETSERIALIZER_HPP

#include <string_view>

#include "Public/Core/Forward.hpp"
#include "Public/IO/Forward.hpp"

#include "log.hpp"
#include "AssetHeader.hpp"
#include "AssetMetadata.hpp"


namespace MeowEngine::Asset {
    // class AssetRegistry;

    /**
     * Reads asset header or writes asset header + given data
     */
    class AssetSerializer {
    public:
        static Serialization::Serializer OpenSerializer(Path path, FileSystem::FileMode mode);
        static void CloseSerializer(const Serialization::Serializer& serializer);

        static bool ReadHeader(const Serialization::Serializer& serializer, AssetHeader& header);
        static void WriteHeader(const Serialization::Serializer& serializer, const AssetHeader& header);

        static void ReadMetadata(const Serialization::Serializer& serializer, AssetMetadata& metadata);
        static void WriteMetadata(const Serialization::Serializer& serializer, const AssetMetadata& metadata);

        static bool CreateEmptyMeowdata(const Path& path, const AssetHeader& header);

    public:
        // TODO: we dont need this anymore
        // this is used for binary data importer -> like png, jpeg and also obj
        static void Serialize(const std::string_view& importPath, const std::string_view& savePath);
    };

}


#endif //MEOWENGINE_ASSETSERIALIZER_HPP
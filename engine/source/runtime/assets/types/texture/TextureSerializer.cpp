//
// Created by Akira Mujawar on 01/07/26.
//

#include "TextureSerializer.hpp"

#include "Public/IO/Include.hpp"
#include "AssetSerializer.hpp"
#include "SDL_API.hpp"

namespace MeowEngine::Asset {
    bool TextureSerializer::Serialize(const Path& path, const std::vector<uint8_t>& data) {
        MeowEngine::Log("TextureSerializer", "Serialize");

        // read existing header
        auto readSerializer = AssetSerializer::OpenSerializer(path, FileSystem::FileMode::READ);
        AssetHeader header;
        AssetSerializer::ReadHeader(readSerializer, header);

        AssetSerializer::CloseSerializer(readSerializer);

        // create temp
        auto tempPath = path;
        tempPath.ReplaceExtension("meowtemp");

        auto writeSerializer = AssetSerializer::OpenSerializer(tempPath, FileSystem::FileMode::WRITE);
        AssetSerializer::WriteHeader(writeSerializer, header);

        // write data
        writeSerializer.WriteByteVector(data);

        // close & get back temp file
        AssetSerializer::CloseSerializer(writeSerializer);

        if (!FileSystem::FileSystem::Replace(path, tempPath)) {
            FileSystem::FileSystem::Remove(tempPath);

            return false;
        }

        return true;
    }

    bool TextureSerializer::Deserialize(const Path& path, BitmapAsset& asset) {
        MeowEngine::Log("TextureSerializer", "Deserialize");

        auto serializer = AssetSerializer::OpenSerializer(path, FileSystem::FileMode::READ);

        // read header
        AssetHeader header;
        bool isValidAsset = AssetSerializer::ReadHeader(serializer, header);

        if (!isValidAsset) {
            return false;
        }

        // read data
        auto data = serializer.ReadByteVector();

        // close serialization
        AssetSerializer::CloseSerializer(serializer);

        // decompress the data
        SDL_RWops* rw = SDL_RWFromConstMem(data.data(), static_cast<int>(data.size()));
        SDL_Surface* source = IMG_Load_RW(rw, 1);
        SDL_Rect imageFrame {0, 0, source->w, source->h};

        uint32_t redMask;
        uint32_t greenMask;
        uint32_t blueMask;
        uint32_t alphaMask;

        // what is Endian?
#if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        redMask = 0xff000000;
        greenMask = 0x00ff0000;
        blueMask = 0x0000ff00;
        alphaMask = 0x000000ff;
#else
        redMask = 0x000000ff;
        greenMask = 0x0000ff00;
        blueMask = 0x00ff0000;
        alphaMask = 0xff000000;
#endif

        SDL_Surface* target {
            SDL_CreateRGBSurface(
                0,
                imageFrame.w,
                imageFrame.h,
                32,
                redMask, greenMask, blueMask, alphaMask
            )
        };

        // copy data from source to target
        SDL_BlitSurface(source, &imageFrame, target, &imageFrame);
        SDL_FreeSurface(source);

        // set asset data
        asset.SetData(target);

        return true;
    }
}

//
// Created by Akira Mujawar on 19/06/24.
//

#ifndef MEOWENGINE_BITMAP_HPP
#define MEOWENGINE_BITMAP_HPP

#pragma once

#include "IAsset.hpp"
#include "internal_ptr.hpp"
#include "SDL_API.hpp"

namespace MeowEngine::Asset  {
    struct BitmapAsset : IAsset {
        BitmapAsset() = default;
        ~BitmapAsset() override;

        void SetData(SDL_Surface* surface);

        [[nodiscard]] uint16_t GetWidth() const { return Surface->w; }
        [[nodiscard]] uint16_t GetHeight() const { return Surface->h; }

        // Gives memory pointer to the data of bitmap. Required for OpenGL/Vulkan
        void* GetPixelData() const { return Surface->pixels; }

    private:
        SDL_Surface* Surface = nullptr;
        // struct Internal;
        // MeowEngine::internal_ptr<Internal> InternalPointer;
    };
}


#endif //MEOWENGINE_BITMAP_HPP

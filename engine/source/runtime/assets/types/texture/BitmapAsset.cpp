//
// Created by Akira Mujawar on 19/06/24.
//

#include "BitmapAsset.hpp"

namespace MeowEngine::Asset {
    BitmapAsset::~BitmapAsset() {
        SDL_FreeSurface(Surface);
    }

    void BitmapAsset::SetData(SDL_Surface* surface) {
        Surface = surface;
    }
}

// struct Bitmap::Internal {
//     SDL_Surface* surface = nullptr;
//
//     Internal() {}
//
//     ~Internal() {
//
//     }
// };
//
// Bitmap::Bitmap() : InternalPointer(MeowEngine::make_internal_ptr<Internal>()) {}
//
// void Bitmap::SetData(SDL_Surface* surface) const {
//     InternalPointer->surface = surface;
// }
//
// uint16_t Bitmap::GetWidth() const {
//     return static_cast<uint16_t>(InternalPointer->surface->w);
// }
//
// uint16_t Bitmap::GetHeight() const {
//     return static_cast<uint16_t>(InternalPointer->surface->h);
// }
//
// // REMEMBER: void* is a generic pointer type and can be casted to other pointer without explicit cast
// void* Bitmap::GetPixelData() const {
//     return InternalPointer->surface->pixels;
// }
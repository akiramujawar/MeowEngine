//
// Created by Akira Mujawar on 05/07/22.
//

#include "PlatformType.hpp"

MeowEngine::PlatformType MeowEngine::GetCurrentPlatform() {
    #if defined(__EMSCRIPTEN__)
        return MeowEngine::PlatformType::emscripten;
    #elif __APPLE__
        #include "TargetConditionals.h"
        #if TARGET_OS_IPHONE
            return MeowEngine::PlatformType::ios;
        #else
            return MeowEngine::PlatformType::mac;
        #endif
    #elif __ANDROID__
        return MeowEngine::PlatformType::android;
    #elif WIN32
        return MeowEngine::PlatformType::windows;
    #endif
}
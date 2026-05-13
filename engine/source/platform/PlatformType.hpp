//
// Created by Akira Mujawar on 05/07/22.
//

#ifndef MEOWENGINE_PLATFORMTYPE_HPP
#define MEOWENGINE_PLATFORMTYPE_HPP

#pragma once

namespace MeowEngine
{
    enum class PlatformType
    {
        ios,
        android,
        windows,
        mac,
        emscripten
    };

    PlatformType GetCurrentPlatform();
} // namespace MeowEngine

#endif //MEOWENGINE_PLATFORMTYPE_HPP


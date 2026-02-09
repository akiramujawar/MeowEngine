//
// Created by Akira Mujawar on 06/07/22.
//

#ifndef VULKAN_ENGINE_LOG_HPP
#define VULKAN_ENGINE_LOG_HPP

#pragma once

#include <string>
#include "tracy_wrapper.hpp"

namespace MeowEngine {
    enum LogType {
        MESSAGE,
        WARNING,
        ERROR
    };

    // Things we need
    // Basic logger while building
    // Logger to track for performance (merging with tracy profiler)
    // In-game logger to debug logs specific to game code

    void Log(const std::string& tag, std::initializer_list<std::string_view> messages, LogType = MESSAGE);

    void Log(const std::string& tag, const std::string& message, LogType = MESSAGE);
    void Log(const std::string& tag, const char* message, LogType = MESSAGE);
    void Log(const std::string& tag, const int& message, LogType = MESSAGE);
    void Log(const std::string& tag, const float& message, LogType = MESSAGE);
    void Log(const std::string& tag, const bool& message, LogType = MESSAGE);

    void Log(const std::string& tag, const std::string& message, const std::exception& error, LogType = MESSAGE);
} // namespace MeowEngine


#endif //VULKAN_ENGINE_LOG_HPP

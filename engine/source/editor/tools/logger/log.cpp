//
// Created by Akira Mujawar on 06/07/22.
//

#ifndef NDEBUG
    #ifdef __ANDROID__
        #include <android/log.h>
    #endif
#endif

#include "log.hpp"
#include "iostream"

namespace MeowEngine {
    void SetLogType(LogType mType) {
        switch (mType) {
            case MESSAGE:
                std::cout << "[MESSAGE] ";
                break;
            case WARNING:
                std::cout << "[WARNING] ";
                break;
            case ERROR:
                std::cout << "[ERROR] ";
                break;
            default:
                break;
        }
    }
}

void MeowEngine::Log(const std::string& tag, std::initializer_list<std::string_view> messages, LogType mType) {
#ifndef NDEBUG
#ifdef __ANDROID__
//    __android_log_print(ANDROID_LOG_DEBUG, "a-simple-triangle", "%s: %s", tag.c_str(), message.c_str());
#else

    SetLogType(mType);

    std::cout << tag;

    for(const auto& message : messages) {
        std::cout << ',' << message;
    }

    std::cout<<std::endl;
#endif
#endif
}

void MeowEngine::Log(const std::string& tag, const std::string& message, LogType mType) {
#ifndef NDEBUG
#ifdef __ANDROID__
    __android_log_print(ANDROID_LOG_DEBUG, "a-simple-triangle", "%s: %s", tag.c_str(), message.c_str());
#else

    SetLogType(mType);

    std::cout << tag << ": " << message << std::endl;
#endif
#endif
}

void MeowEngine::Log(const std::string& tag, const char* message, LogType mType) {
#ifndef NDEBUG
#ifdef __ANDROID__
    __android_log_print(ANDROID_LOG_DEBUG, "a-simple-triangle", "%s: %s", tag.c_str(), message.c_str());
#else
    SetLogType(mType);

    std::cout << tag << ": " << message << std::endl;
#endif
#endif
}

void MeowEngine::Log(const std::string& tag, const int& message, LogType mType) {
#ifndef NDEBUG
#ifdef __ANDROID__
//    __android_log_print(ANDROID_LOG_DEBUG, "a-simple-triangle", "%s: %s", tag.c_str(), message.c_str());
#else
    SetLogType(mType);

    std::cout << tag << ": " << message << std::endl;
#endif
#endif
}

void MeowEngine::Log(const std::string& tag, const float& message, LogType mType) {
#ifndef NDEBUG
#ifdef __ANDROID__
    //    __android_log_print(ANDROID_LOG_DEBUG, "a-simple-triangle", "%s: %s", tag.c_str(), message.c_str());
#else
    SetLogType(mType);

    std::cout << tag << ": " << message << std::endl;
#endif
#endif
}

void MeowEngine::Log(const std::string& tag, const bool& message, LogType mType) {
#ifndef NDEBUG
#ifdef __ANDROID__
    //    __android_log_print(ANDROID_LOG_DEBUG, "a-simple-triangle", "%s: %s", tag.c_str(), message.c_str());
#else
    SetLogType(mType);

    if(message) {
        std::cout << tag << ": " << "true"<< std::endl;
    }
    else {
        std::cout << tag << ": " << "false" << std::endl;
    }

#endif
#endif
}

void MeowEngine::Log(const std::string& tag, const std::string& message, const std::exception& error, LogType mType) {
    #ifndef NDEBUG
        std::string output = message + " Exception message was: " + std::string{error.what()};

    SetLogType(mType);
    MeowEngine::Log(tag, output);
    #endif
}

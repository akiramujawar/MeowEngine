//
// Created by Akira Mujawar on 09/01/25.
//

#ifndef MEOWENGINE_STRING_HPP
#define MEOWENGINE_STRING_HPP

#include "string"
#include "Object.hpp"

namespace MeowEngine::Core::Types {
    class String : public std::string {

    public:
        REFLECT_VALUE(String)
        static void Reflect() {}

        String();
        String(std::string inString);

        template<typename... Args>
        static std::string Format(const char* fmt, Args... args)
        {
            size_t size = snprintf(nullptr, 0, fmt, args...);
            std::string buf;
            buf.reserve(size + 1);
            buf.resize(size);
            snprintf(&buf[0], size + 1, fmt, args...);
            return buf;
        }
    };
}

#endif //MEOWENGINE_STRING_HPP

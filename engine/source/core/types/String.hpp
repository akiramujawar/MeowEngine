//
// Created by Akira Mujawar on 09/01/25.
//

#ifndef MEOWENGINE_STRING_HPP
#define MEOWENGINE_STRING_HPP

#include <reflection_macro_wrapper.hpp>
#include <string>

namespace MeowEngine::Core::Types {
    /**
     * Custom string representation for our engine to handle reflection and add functionality
     * NOTE: Avoiding inheritance from stl lib to avoid implicit conversions and no virtual destructor
     */
    struct String {

    public:
        REFLECT_VALUE(String)
        static void Reflect();

        String();
        explicit String(const std::string& string);

        /**
         * Split from end to start
         * @param pDelimiter
         * @return
         */
        [[nodiscard]] std::vector<std::string> SplitR(const std::string& pDelimiter) const;

        [[nodiscard]] const char* CStr() const;
        char* Data();

    private:
        std::string Value;

    public:
        template<typename... Args>
        static std::string Format(const char* fmt, Args... args);
    };

    template <typename ... Args>
    std::string String::Format(const char* fmt, Args... args) {
        size_t size = snprintf(nullptr, 0, fmt, args...);
        std::string buf;
        buf.reserve(size + 1);
        buf.resize(size);
        snprintf(&buf[0], size + 1, fmt, args...);
        return buf;
    }
}

#endif //MEOWENGINE_STRING_HPP

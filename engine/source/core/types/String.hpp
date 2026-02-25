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

        /**
         * Split from end to start
         * @param pDelimiter
         * @return
         */
        std::vector<std::string> SplitR(const std::string& pDelimiter) {
            size_t nextIndex = 0;
            std::vector<std::string> names;
            size_t lastIndex = size()- 1;

            while(true) {
                nextIndex = rfind(pDelimiter, lastIndex);

                if(nextIndex == std::string::npos) {
                    names.push_back(substr(0, lastIndex));
                    break;
                }

                names.push_back(substr(nextIndex + 1, lastIndex - nextIndex + 1));

                if(nextIndex == 0) {
                    break;
                }

                lastIndex = nextIndex - pDelimiter.size();
            }
        }
    };
}

#endif //MEOWENGINE_STRING_HPP

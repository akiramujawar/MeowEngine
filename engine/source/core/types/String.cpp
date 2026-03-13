//
// Created by Akira Mujawar on 09/01/25.
//

#include <String.hpp>


namespace MeowEngine::Core::Types {
    void String::Reflect() {
        REGISTER_PROPERTY(String, Value, std::string, true, true);
    }

    String::String() = default;

    String::String(const std::string& string) {
        Value.assign(string);
    }

    std::vector<std::string> String::SplitR(const std::string& pDelimiter) const {
        size_t nextIndex = 0;
        std::vector<std::string> names;
        size_t lastIndex = Value.size()- 1;

        while(true) {
            nextIndex = Value.rfind(pDelimiter, lastIndex);

            if(nextIndex == std::string::npos) {
                names.push_back(Value.substr(0, lastIndex));
                break;
            }

            names.push_back(Value.substr(nextIndex + 1, lastIndex - nextIndex + 1));

            if(nextIndex == 0) {
                break;
            }

            lastIndex = nextIndex - pDelimiter.size();
        }

        return names;
    }

    const char* String::CStr() const {
        return Value.c_str();
    }

    char* String::Data() {
        return Value.data();
    }
}

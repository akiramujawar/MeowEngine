//
// Created by Akira Mujawar on 24/02/26.
//

#include "WebAddress.hpp"



namespace MeowEngine::Core::Types {
    WebAddress::WebAddress(const std::string& string) {
        URL.assign(string);
    }

    const char* WebAddress::CStr() const {
        return URL.c_str();
    }
}

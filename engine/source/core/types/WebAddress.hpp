//
// Created by Akira Mujawar on 24/02/26.
//

#ifndef MEOWENGINE_WEBADDRESS_HPP
#define MEOWENGINE_WEBADDRESS_HPP

#include <string>

namespace MeowEngine::Core::Types {

    struct WebAddress {
        explicit WebAddress(const std::string& string);

        [[nodiscard]] const char* CStr() const;

    private:
        std::string URL;
    };

}


#endif //MEOWENGINE_WEBADDRESS_HPP

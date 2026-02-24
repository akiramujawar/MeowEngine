//
// Created by Akira Mujawar on 09/01/25.
//

#include "String.hpp"
#include "log.hpp"

namespace MeowEngine::Core::Types {

    String::String() {

    }

    String::String(std::string inString) {
        this->assign(inString);
    }

}
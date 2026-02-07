//
// Created by Akira Mujawar on 09/01/25.
//

#include "pstring.hpp"
#include "log.hpp"


MeowEngine::PString::PString() {

}

MeowEngine::PString::PString(std::string inString) {
    this->assign(inString);
}
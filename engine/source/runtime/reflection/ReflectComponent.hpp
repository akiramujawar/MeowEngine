//
// Created by Akira Mujawar on 11/06/26.
//

#ifndef MEOWENGINE_REFLECTCOMPONENT_HPP
#define MEOWENGINE_REFLECTCOMPONENT_HPP

#include "string"
#include "functional"

namespace MeowEngine {
    struct ReflectionComponent {
        std::string ClassName;

        /**
         * Constructs new component (delete manually after usage)
         */
        std::function<void*()> Construct;
        std::function<void(void*)> Destruct;
    };
}

#endif //MEOWENGINE_REFLECTCOMPONENT_HPP
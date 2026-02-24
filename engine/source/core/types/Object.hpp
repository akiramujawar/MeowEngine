//
// Created by Akira Mujawar on 03/02/26.
//

#ifndef MEOWENGINE_OBJECT_HPP
#define MEOWENGINE_OBJECT_HPP

#include "string"
#include "reflection_macro_wrapper.hpp"

namespace MeowEngine::Core::Types {
    /**
     * This class is important for reflections of class object pointers
     * Any pointer which needs to be displayed has to be derived from MObject
     */
    class Object {
    public:
        virtual ~Object() = default;
        virtual std::string GetClassName() = 0;
    };
}


#endif //MEOWENGINE_OBJECT_HPP

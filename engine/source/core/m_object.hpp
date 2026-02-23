//
// Created by Akira Mujawar on 03/02/26.
//

#ifndef MEOWENGINE_M_OBJECT_HPP
#define MEOWENGINE_M_OBJECT_HPP

#include "string"
#include "reflection_macro_wrapper.hpp"

namespace MeowEngine::entity {
    /**
     * This class is important for reflections of class object pointers
     * Any pointer which needs to be displayed has to be derived from MObject
     */
    class MObject {
    public:
        virtual ~MObject() = default;
        virtual std::string GetClassName() = 0;
    };
}


#endif //MEOWENGINE_M_OBJECT_HPP

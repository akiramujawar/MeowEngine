//
// Created by Akira Mujawar on 08/01/25.
//

#ifndef MEOWENGINE_REFLECTION_PROPERTY_HPP
#define MEOWENGINE_REFLECTION_PROPERTY_HPP

#include "string"
#include "functional"
#include "property_type.hpp"

using namespace std;

namespace MeowEngine {
    struct ReflectionProperty {
        std::string Name; // name of property
        MeowEngine::PropertyType Type; // type of class
        const type_info& TypeId; // type id of class
        std::string TypeName; // name of class
        bool IsEditable; // can property be edited in ui
        bool IsMObject; // is the property derived from MObject

        std::function<void (void*, const void*)> Set;
        std::function<void* (void*)> Get;
        std::function<void (void*)> Callback;
    };
}

#endif //MEOWENGINE_REFLECTION_PROPERTY_HPP

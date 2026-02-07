//
// Created by Akira Mujawar on 08/01/25.
//
//#pragma once

#ifndef MEOWENGINE_REFLECTION_MACRO_WRAPPER_HPP
#define MEOWENGINE_REFLECTION_MACRO_WRAPPER_HPP

#include "entt_reflection.hpp"

namespace MeowEngine {
    // static will make sure that there's only one instance of Reflection in engine lifetime
    // inline will allow multiple identical function definitions as this macro is used has header in many files
    // canonical C++ pattern
    // these are called at runtime initialisation before main method
    // be aware, that, that will prevent from us debugging any code on these calls
    inline MeowEngine::EnttReflection& GetReflection() {
        static MeowEngine::EnttReflection ReflectionTest {};

        return ReflectionTest;
    }

    // Essentially results in calling a static Reflect method while initialisation
    // of engine
    #define REFLECT(Type) \
        \
        struct Type##Reflecter {            \
            Type##Reflecter() {             \
                Type::Reflect();            \
            }                               \
        };                                  \
        \
        inline static Type##Reflecter _reflecter{};


    #define REGISTER_COMPONENT(Component) \
                                          \
        MeowEngine::GetReflection().RegisterComponent<Component>(\
            #Component\
        );

    // objectPointer -
    #define REGISTER_PROPERTY(Class, Property, Type) \
        MeowEngine::GetReflection().RegisterProperty(\
            #Class,\
            {\
                #Property,                          \
                GetPropertyType<Type>(),                                    \
                GetPropertyTypeId<Type>(),          \
                #Type,                                        \
                true,                                              \
                [](void* objectPointer, const void* value) { ((Class*)objectPointer)->Property = *(Type*)value; },\
                [](void* objectPointer) -> void* { return &(((Class*)objectPointer)->Property); }, \
                [](void* objectPointer) -> void {} \
            }\
        );

    #define REGISTER_PROPERTY_CALLBACK(Class, Property, Type, Callback)\
        MeowEngine::GetReflection().RegisterProperty(\
            #Class,\
            {\
                #Property,                          \
                GetPropertyType<Type>(),                                    \
                GetPropertyTypeId<Type>(),          \
                #Type,                                        \
                true,                                              \
                [](void* objectPointer, const void* value) { ((Class*)objectPointer)->Property = *(Type*)value; },\
                [](void* objectPointer) -> void* { return &(((Class*)objectPointer)->Property);}, \
                [](void* objectPointer) -> void { ((Class*)objectPointer)->Callback(); } \
            }\
        );

    #define REGISTER_POINTER(Class, Property, Type, IsMObject)\
        MeowEngine::GetReflection().RegisterProperty(\
            #Class,\
            {\
                #Property,                          \
                GetPropertyType<Type>(),                                    \
                GetPropertyTypeId<Type>(),          \
                #Type,                                        \
                IsMObject, \
                [](void* objectPointer, const void* value) { ((Class*)objectPointer)->Property = *(Type*)value; },\
                [](void* objectPointer) -> void* { return &(((Class*)objectPointer)->Property);},                 \
                [](void* objectPointer) -> void {} \
            }\
        );

    #define REGISTER_POINTER_CALLBACK(Class, Property, Type, IsMObject, Callback)\
        MeowEngine::GetReflection().RegisterProperty(\
            #Class,\
            {\
                #Property,                          \
                GetPropertyType<Type>(),                                    \
                GetPropertyTypeId<Type>(),          \
                #Type,                                        \
                IsMObject, \
                [](void* objectPointer, const void* value) { ((Class*)objectPointer)->Property = *(Type*)value; },\
                [](void* objectPointer) -> void* { return &(((Class*)objectPointer)->Property);},                 \
                [](void* objectPointer) -> void { ((Class*)objectPointer)->Callback(); } \
            }\
        );

    #define REGISTER_ENUM(Class, Property, Type)\
        MeowEngine::GetReflection().RegisterProperty(\
            #Class,\
            {\
                #Property,                          \
                GetPropertyType<Type>(),                                    \
                GetPropertyTypeId<Type>(),          \
                #Type,                          \
                true, \
                [](void* objectPointer, const void* value) { ((Class*)objectPointer)->Property = *(Type*)value; },\
                [](void* objectPointer) -> void* { return &(((Class*)objectPointer)->Property);},\
                [](void* objectPointer) -> void {} \
            }\
        );

    #define REGISTER_ENUM_CALLBACK(Class, Property, Type, Callback)\
        MeowEngine::GetReflection().RegisterProperty(\
            #Class,\
            {\
                #Property,                          \
                GetPropertyType<Type>(),                                    \
                GetPropertyTypeId<Type>(),          \
                #Type,                          \
                true, \
                [](void* objectPointer, const void* value) { ((Class*)objectPointer)->Property = *(Type*)value; },\
                [](void* objectPointer) -> void* { return &(((Class*)objectPointer)->Property);},\
                [](void* objectPointer) -> void { ((Class*)objectPointer)->Callback(); } \
            }\
        );

}
#endif //MEOWENGINE_REFLECTION_MACRO_WRAPPER_HPP

//
// Created by Akira Mujawar on 08/01/25.
//
//#pragma once

#ifndef MEOWENGINE_ENTT_REFLECTION_WRAPPER_HPP
#define MEOWENGINE_ENTT_REFLECTION_WRAPPER_HPP

#include "entt_reflection.hpp"

namespace MeowEngine {
    extern MeowEngine::EnttReflection Reflection;

    // SPINAE principle :- substitution failure is not a error
    #define REFLECT(Type) MeowEngine::Reflection.Reflect<Type>()

    #define REGISTER_ENTT_COMPONENT(Component) \
        \
        MeowEngine::Reflection.RegisterComponent(\
            entt::type_hash<Component>().value(), \
            #Component\
        );\
        \
        REFLECT(Component);



    // objectPointer -
    #define REGISTER_PROPERTY(Class, Property, Type) \
        MeowEngine::Reflection.RegisterProperty(\
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
        );\
        \
        REFLECT(Type);

    #define REGISTER_PROPERTY_CALLBACK(Class, Property, Type, Callback)\
        MeowEngine::Reflection.RegisterProperty(\
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
        );\
        \
        REFLECT(Type);

    #define REGISTER_POINTER(Class, Property, Type, IsMObject)\
        MeowEngine::Reflection.RegisterProperty(\
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
        );\
        \
        REFLECT(Type);

    #define REGISTER_POINTER_CALLBACK(Class, Property, Type, IsMObject, Callback)\
        MeowEngine::Reflection.RegisterProperty(\
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
        );\
        \
        REFLECT(Type);

    #define REGISTER_ENUM(Class, Property, Type)\
        MeowEngine::Reflection.RegisterProperty(\
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
        );\
        \
        REFLECT(Type);

    #define REGISTER_ENUM_CALLBACK(Class, Property, Type, Callback)\
        MeowEngine::Reflection.RegisterProperty(\
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
        );\
        \
        REFLECT(Type);

}
#endif //MEOWENGINE_ENTT_REFLECTION_WRAPPER_HPP

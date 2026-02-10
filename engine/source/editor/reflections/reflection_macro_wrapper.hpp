//
// Created by Akira Mujawar on 08/01/25.
//
//#pragma once

#ifndef MEOWENGINE_REFLECTION_MACRO_WRAPPER_HPP
#define MEOWENGINE_REFLECTION_MACRO_WRAPPER_HPP

#include "entt_reflection.hpp"

namespace MeowEngine {
    /**
     * Converts the parameter into a string
     * GET_STRING(name) defined below, combines the input and sends the value
     * so instead of get "Type" we get "whatever the value is"
     */
    #define GET_STRING_IMPLEMENTATION(Type) #Type

    /**
     * Converts the parameter into a string
     */
    #define GET_STRING(Type) GET_STRING_IMPLEMENTATION(Type)

    // static will make sure that there's only one instance of Reflection in engine lifetime
    // inline will allow multiple identical function definitions as this macro is used has header in many files
    // canonical C++ pattern
    // these are called at runtime initialisation before main method
    // be aware, that, that will prevent from us debugging any code on these calls
    inline MeowEngine::EnttReflection& GetReflection() {
        static MeowEngine::EnttReflection Reflection {};

        return Reflection;
    }

    // Essentially results in calling a static Reflect method while initialisation
    // of engine
    #define REFLECT_MObject(Type) \
        \
        struct Type##Reflector {            \
            Type##Reflector() {             \
                Type::Reflect();            \
            }                               \
        };                                  \
        \
        inline static Type##Reflector _reflector{}; \
        std::string GetClassName() override { \
            return #Type; \
        }

    /**
     * Reflects component for showing up in UI & tracking property changes
     * Registers as component in reflection system
     * Creates a callback for caching component within EnttTripleBuffer register which, later is executed on scene load
     * (caching is required in order to create a sequenced
     * component id for each component on buffers (main, render & physics))
     */
    #define REFLECT_COMPONENT(Type) \
        \
        struct Type##Reflector {            \
            Type##Reflector(void(*pCallback)(void *)) {     \
                REGISTER_COMPONENT(Type);                \
                Type::Reflect();    \
                MeowEngine::GetReflection().AddInitialiseComponentCallback(pCallback); \
            }                               \
        };                                  \
        \
        inline static Type##Reflector _reflector{           \
         &MeowEngine::EnttReflection::RegisterComponentOnEnttBuffer<Type> \
        };                          \
        std::string GetClassName() override { \
            return #Type; \
        }



    /**
     * ideally we can also forward declare enum and use it before giving definitions to enums
     * in current case above method could work as templates are initialised at later stages
     * but could break if we create modules like dll files. need more research on this topic for
     * safety reasons,
     * we will have to place the this call after enums are declared.
     */
    #define REFLECT_ENUM(Namespace, Type) \
        namespace __ENUMS {                       \
            struct Type##Reflector { \
                Type##Reflector() { \
                    MeowEngine::GetReflection().RegisterEnum<Namespace::Type>(GET_STRING(Namespace::Type)); \
                } \
            }; \
            inline __ENUMS::Type##Reflector __reflector##Type{};                                                     \
        }

    #define REGISTER_COMPONENT(Component) \
                                          \
        MeowEngine::GetReflection().RegisterComponent<Component>(\
            #Component\
        );

    // objectPointer -
    #define REGISTER_PROPERTY(Class, Property, Type, IsEditable, IsMObject) \
        MeowEngine::GetReflection().RegisterProperty(\
            #Class,\
            {\
                #Property,                          \
                GetPropertyType<Type>(),                                    \
                GetPropertyTypeId<Type>(),          \
                #Type,                                           \
                IsEditable, \
                IsMObject,                                              \
                [](void* objectPointer, const void* value) { ((Class*)objectPointer)->Property = *(Type*)value; },\
                [](void* objectPointer) -> void* { return &(((Class*)objectPointer)->Property); }, \
                [](void* objectPointer) -> void {} \
            }\
        );

    #define REGISTER_PROPERTY_CALLBACK(Class, Property, Type, IsEditable, IsMObject, Callback)\
        MeowEngine::GetReflection().RegisterProperty(\
            #Class,\
            {\
                #Property,                          \
                GetPropertyType<Type>(),                                    \
                GetPropertyTypeId<Type>(),          \
                #Type,                                                             \
                IsEditable, \
                IsMObject,                                              \
                [](void* objectPointer, const void* value) { ((Class*)objectPointer)->Property = *(Type*)value; },\
                [](void* objectPointer) -> void* { return &(((Class*)objectPointer)->Property);}, \
                [](void* objectPointer) -> void { ((Class*)objectPointer)->Callback(); } \
            }\
        );

    #define REGISTER_POINTER(Class, Property, Type, IsEditable, IsMObject)\
        MeowEngine::GetReflection().RegisterProperty(\
            #Class,\
            {\
                #Property,                          \
                GetPropertyType<Type>(),                                    \
                GetPropertyTypeId<Type>(),          \
                #Type,                                                    \
                IsEditable, \
                IsMObject, \
                [](void* objectPointer, const void* value) { ((Class*)objectPointer)->Property = *(Type*)value; },\
                [](void* objectPointer) -> void* { return &(((Class*)objectPointer)->Property);},                 \
                [](void* objectPointer) -> void {} \
            }\
        );

    #define REGISTER_POINTER_CALLBACK(Class, Property, Type, IsEditable, IsMObject, Callback)\
        MeowEngine::GetReflection().RegisterProperty(\
            #Class,\
            {\
                #Property,                          \
                GetPropertyType<Type>(),                                    \
                GetPropertyTypeId<Type>(),          \
                #Type,                                                                       \
                IsEditable, \
                IsMObject, \
                [](void* objectPointer, const void* value) { ((Class*)objectPointer)->Property = *(Type*)value; },\
                [](void* objectPointer) -> void* { return &(((Class*)objectPointer)->Property);},                 \
                [](void* objectPointer) -> void { ((Class*)objectPointer)->Callback(); } \
            }\
        );

    #define REGISTER_ENUM(Class, Property, Type, IsEditable)\
        MeowEngine::GetReflection().RegisterProperty(\
            #Class,\
            {\
                #Property,                          \
                GetPropertyType<Type>(),                                    \
                GetPropertyTypeId<Type>(),          \
                #Type,                                      \
                IsEditable, \
                true, \
                [](void* objectPointer, const void* value) { ((Class*)objectPointer)->Property = *(Type*)value; },\
                [](void* objectPointer) -> void* { return &(((Class*)objectPointer)->Property);},\
                [](void* objectPointer) -> void {} \
            }\
        );

    #define REGISTER_ENUM_CALLBACK(Class, Property, Type, IsEditable, Callback)\
        MeowEngine::GetReflection().RegisterProperty(\
            #Class,\
            {\
                #Property,                          \
                GetPropertyType<Type>(),                                    \
                GetPropertyTypeId<Type>(),          \
                #Type,                                                         \
                IsEditable, \
                true, \
                [](void* objectPointer, const void* value) { ((Class*)objectPointer)->Property = *(Type*)value; },\
                [](void* objectPointer) -> void* { return &(((Class*)objectPointer)->Property);},\
                [](void* objectPointer) -> void { ((Class*)objectPointer)->Callback(); } \
            }\
        );

}
#endif //MEOWENGINE_REFLECTION_MACRO_WRAPPER_HPP

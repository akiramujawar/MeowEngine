//
// Created by Akira Mujawar on 25/06/26.
//

#ifndef MEOWENGINE_REFLECTVALUECLASS_HPP
#define MEOWENGINE_REFLECTVALUECLASS_HPP

// Essentially results in calling a static Reflect method while initialisation
// of engine
#define REFLECT_VALUE(Type) \
    \
    struct Type##Reflector {            \
        Type##Reflector() {             \
            Type::Reflect();            \
        }                               \
    };                                  \
\
inline static Type##Reflector _reflector{};

#endif //MEOWENGINE_REFLECTVALUECLASS_HPP
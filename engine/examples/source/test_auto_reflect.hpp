//
// Created by Akira Mujawar on 05/02/26.
//

#ifndef MEOWENGINE_TEST_AUTO_REFLECT_HPP
#define MEOWENGINE_TEST_AUTO_REFLECT_HPP

#include "log.hpp"
#include "Core.hpp"

// Static Self Registration Test for reflection system
// This is to avoid manual registration of MObjects
class TestAutoReflect : MeowEngine::Object {

    REFLECT_MObject(TestAutoReflect)
    static void Reflect() {
        MeowEngine::EnttReflection& reflection = MeowEngine::GetReflection();
    }
};



#endif //MEOWENGINE_TEST_AUTO_REFLECT_HPP

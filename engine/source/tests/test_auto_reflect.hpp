//
// Created by Akira Mujawar on 05/02/26.
//

#ifndef MEOWENGINE_TEST_AUTO_REFLECT_HPP
#define MEOWENGINE_TEST_AUTO_REFLECT_HPP

#include "log.hpp"

// Static Self Registration Test for reflection system
// This is to avoid manual registration of MObjects
class TestAutoReflect {
    static void Reflect() {
        MeowEngine::Log("Reflect", "TestAutoReflect");
    }

    struct TestAutoRegister {
        TestAutoRegister() {
            // pass the comp type to reflection
            TestAutoReflect::Reflect();
            MeowEngine::Log("Test", "Test Auto Register Created");
        }
    };

    // inline here allows to assign value to auto register
    inline static TestAutoRegister _autoRegister{};
};


#endif //MEOWENGINE_TEST_AUTO_REFLECT_HPP

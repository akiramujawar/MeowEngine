//
// Created by Akira Mujawar on 04/02/26.
//

#ifndef MEOWENGINE_REFLECTION_TEST_COMPONENT_HPP
#define MEOWENGINE_REFLECTION_TEST_COMPONENT_HPP

#include <pstring.hpp>
#include <collider_type.hpp>
#include "component_base.hpp"

namespace MeowEngine::entity {
    class BasicClass {
    public:
        static void Reflect();

        int TestValue;
    };
    class SubChildClass : MObject {
    public:
        static void Reflect();

        std::string GetClassName() override {
            return "SubChildClass";
        };

        int MeshType;
        float Size;
        PString Text; // unable to modify this
    };

    class ChildClass : MObject {
    public:
        static void Reflect();

        std::string GetClassName() override {
            return "ChildClass";
        };

        int ChildMeshType;
        float ChildSize;
        PString ChildText;

        SubChildClass* ChildSubPointer;
    };

    class DummyClass : MObject {
    public:
        static void Reflect();

        std::string GetClassName() override {
            return "DummyClass";
        };

        int RootMeshType;
        float RootSize;
        PString RootText;

        ChildClass RootChild;
        ChildClass* RootChildPointer;
        BasicClass* BasicClassNull;
        BasicClass* BasicClassNonNull;
    };

    class ReflectionTestComponent : public MeowEngine::entity::ComponentBase {
    public:
        static void Reflect();

        ReflectionTestComponent();

        std::string GetClassName() override {
            return "ReflectionTestComponent";
        };

        entity::ColliderType Type;
        DummyClass Data;
    };
}


#endif //MEOWENGINE_REFLECTION_TEST_COMPONENT_HPP

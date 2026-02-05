//
// Created by Akira Mujawar on 04/02/26.
//

#ifndef MEOWENGINE_REFLECTION_TEST_COMPONENT_HPP
#define MEOWENGINE_REFLECTION_TEST_COMPONENT_HPP

#include <pstring.hpp>
#include <collider_type.hpp>
#include <log.hpp>
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

        DummyClass() {
            RootChildPointer = new ChildClass();
            RootChildPointer->ChildSubPointer = new SubChildClass();
            RootChild.ChildSubPointer = new SubChildClass();

            BasicClassNonNull = new BasicClass();
        }

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

        int Int;
        int IntCallback;

        DummyClass Object;
        DummyClass ObjectCallback;

        DummyClass* Pointer;
        DummyClass* PointerCallback;

        entity::ColliderType Enum;
        entity::ColliderType EnumCallback;


        // NOTE: add test for pointer callback & enum callback
        // Quaternion display
        // Automated reflection for classes
        // Editable / non-editable reflection



        void OnIntReflect() {
            MeowEngine::Log("OnIntReflect", "IntCallback Updated");
        }

        void OnObjectReflect() {
            MeowEngine::Log("OnObjectReflect", "ObjectCallback Updated");
        }

        void OnPointerReflect() {
            MeowEngine::Log("OnPointerReflect", "PointerCallback Updated");
        }

        void OnEnumReflect() {
            MeowEngine::Log("OnEnumReflect", "EnumCallback Updated");
        }
    };
}


#endif //MEOWENGINE_REFLECTION_TEST_COMPONENT_HPP

//
// Created by Akira Mujawar on 04/02/26.
//

#ifndef MEOWENGINE_REFLECTION_TEST_COMPONENT_HPP
#define MEOWENGINE_REFLECTION_TEST_COMPONENT_HPP

#include <String.hpp>
#include <collider_shape_type.hpp>
#include <log.hpp>
#include "ComponentBase.hpp"

namespace MeowEngine::Runtime {
    class BasicClass {
    public:
        int TestValue;

        void Init() {
            TestValue = 222;
        }

        BasicClass() {

        }
    };

    class SubChildClass : Object {
    public:
        REFLECT_MObject(SubChildClass)
        static void Reflect();

        void Init() {
            MeshType = 99;
            Size = 99.99;
            Text = String("SubChildClass");
        }

        int MeshType;
        float Size;
        String Text; // unable to modify this
    };

    class ChildClass : Object {
    public:
        REFLECT_MObject(ChildClass)
        static void Reflect();

        void Init() {
            ChildMeshType = 99;
            ChildSize = 99.99;
            ChildText = String("ChildText");

            ChildSubPointer->Init();
        }

        int ChildMeshType;
        float ChildSize;
        String ChildText;

        SubChildClass* ChildSubPointer;
    };

    class DummyClass : Object {
    public:
        REFLECT_MObject(DummyClass)
        static void Reflect();

        DummyClass() {
            RootChildPointer = new ChildClass();
            RootChildPointer->ChildSubPointer = new SubChildClass();
            RootChild.ChildSubPointer = new SubChildClass();

            BasicClassNonNull = new BasicClass();
        }

        void Init() {
            RootMeshType = 99;
            RootSize = 99.99;
            RootText = String("DummyClass");

            RootChild.Init();
            RootChildPointer->Init();
            // BasicClassNull->Init();
            BasicClassNonNull->Init();
        }

        int RootMeshType;
        float RootSize;
        String RootText;

        ChildClass RootChild;
        ChildClass* RootChildPointer;
        BasicClass* BasicClassNull;
        BasicClass* BasicClassNonNull;
    };

    class ReflectionTestComponent : public MeowEngine::Runtime::ComponentBase {
    public:
        REFLECT_COMPONENT(ReflectionTestComponent)
        static void Reflect();

        ReflectionTestComponent();

        int Int;
        int IntCallback;

        DummyClass Object;
        DummyClass ObjectCallback;

        DummyClass* Pointer;
        DummyClass* PointerCallback;

        Runtime::ColliderType Enum;
        Runtime::ColliderType EnumCallback;

        void Init() {
            Int = 111;
            IntCallback = 112;

            Object.Init();
            ObjectCallback.Init();

            Pointer->Init();
            PointerCallback->Init();

            Enum = Runtime::ColliderType::MESH;
            EnumCallback = Runtime::ColliderType::CAPSULE;
        }


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

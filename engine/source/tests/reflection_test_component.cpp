//
// Created by Akira Mujawar on 04/02/26.
//

#include "reflection_test_component.hpp"
#include "reflection_macro_wrapper.hpp"

MeowEngine::entity::ReflectionTestComponent::ReflectionTestComponent()
: Int(10)
, IntCallback(12)
, Object()
, ObjectCallback()
, Enum(entity::ColliderType::SPHERE)
, EnumCallback(entity::ColliderType::SPHERE) {
    Pointer = new DummyClass();
    PointerCallback = new DummyClass();
}

void MeowEngine::entity::SubChildClass::Reflect() {
    REGISTER_PROPERTY(SubChildClass, MeshType, int, true);
    REGISTER_PROPERTY(SubChildClass, Size, float, true);
    REGISTER_PROPERTY(SubChildClass, Text, PString, true);
}

void MeowEngine::entity::ChildClass::Reflect() {
    REGISTER_PROPERTY(ChildClass, ChildMeshType, int, true);
    REGISTER_PROPERTY(ChildClass, ChildSize, float, true);
    REGISTER_PROPERTY(ChildClass, ChildText, PString, true);
    REGISTER_POINTER(ChildClass, ChildSubPointer, SubChildClass*, true, true);

//    MeowEngine::Reflection.Reflect<SubChildClass>();
}

void MeowEngine::entity::DummyClass::Reflect() {
//    MeowEngine::Reflection.Reflect<ChildClass>();
//    MeowEngine::Reflection.Reflect<DummyClass>();

    REGISTER_PROPERTY(DummyClass, RootMeshType, int, true);
    REGISTER_PROPERTY(DummyClass, RootSize, float, true);

    REGISTER_PROPERTY(DummyClass, RootChild, ChildClass, true);
    REGISTER_POINTER(DummyClass, RootChildPointer, ChildClass*, true, true);
    REGISTER_PROPERTY(DummyClass, RootText, PString, true);

    REGISTER_POINTER(DummyClass, BasicClassNull, BasicClass*, true, false);
    REGISTER_POINTER(DummyClass, BasicClassNonNull, BasicClass*, true, false);
}

void MeowEngine::entity::ReflectionTestComponent::Reflect() {
    REGISTER_PROPERTY(ReflectionTestComponent, Int, int, true); // primitive
    REGISTER_PROPERTY_CALLBACK(ReflectionTestComponent, IntCallback, int, true, OnIntReflect); // primitive callback

    REGISTER_PROPERTY(ReflectionTestComponent, Object, DummyClass, true); // class object
    REGISTER_PROPERTY_CALLBACK(ReflectionTestComponent, ObjectCallback, DummyClass, true, OnObjectReflect); // class object callback

    REGISTER_POINTER(ReflectionTestComponent, Pointer, DummyClass*, true, true); // pointer object
    REGISTER_POINTER_CALLBACK(ReflectionTestComponent, PointerCallback, DummyClass*, true, true, OnPointerReflect); // pointer object callback

    REGISTER_ENUM(ReflectionTestComponent, Enum, MeowEngine::entity::ColliderType, true); // enum
    REGISTER_ENUM_CALLBACK(ReflectionTestComponent, EnumCallback, MeowEngine::entity::ColliderType, true, OnEnumReflect); // enum callback
}
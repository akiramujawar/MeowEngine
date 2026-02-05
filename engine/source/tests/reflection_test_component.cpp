//
// Created by Akira Mujawar on 04/02/26.
//

#include "reflection_test_component.hpp"
#include "entt_reflection_wrapper.hpp"

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

void MeowEngine::entity::BasicClass::Reflect() {
    REGISTER_PROPERTY(BasicClass, TestValue, int);
}

void MeowEngine::entity::SubChildClass::Reflect() {
    REGISTER_PROPERTY(SubChildClass, MeshType, int);
    REGISTER_PROPERTY(SubChildClass, Size, float);
    REGISTER_PROPERTY(SubChildClass, Text, PString);
}

void MeowEngine::entity::ChildClass::Reflect() {
    REGISTER_PROPERTY(ChildClass, ChildMeshType, int);
    REGISTER_PROPERTY(ChildClass, ChildSize, float);
    REGISTER_PROPERTY(ChildClass, ChildText, PString);
    REGISTER_POINTER(ChildClass, ChildSubPointer, SubChildClass*, true);

    MeowEngine::Reflection.Reflect<SubChildClass>();
}

void MeowEngine::entity::DummyClass::Reflect() {
//    MeowEngine::Reflection.Reflect<ChildClass>();
//    MeowEngine::Reflection.Reflect<DummyClass>();

    REGISTER_PROPERTY(DummyClass, RootMeshType, int);
    REGISTER_PROPERTY(DummyClass, RootSize, float);

    REGISTER_PROPERTY(DummyClass, RootChild, ChildClass);
    REGISTER_POINTER(DummyClass, RootChildPointer, ChildClass*, true);
    REGISTER_PROPERTY(DummyClass, RootText, PString);

    REGISTER_POINTER(DummyClass, BasicClassNull, BasicClass*, false);
    REGISTER_POINTER(DummyClass, BasicClassNonNull, BasicClass*, false);
}

void MeowEngine::entity::ReflectionTestComponent::Reflect() {
    REGISTER_PROPERTY(ReflectionTestComponent, Int, int); // primitive
    REGISTER_PROPERTY_CALLBACK(ReflectionTestComponent, IntCallback, int, OnIntReflect); // primitive callback

    REGISTER_PROPERTY(ReflectionTestComponent, Object, DummyClass); // class object
    REGISTER_PROPERTY_CALLBACK(ReflectionTestComponent, ObjectCallback, DummyClass, OnObjectReflect); // class object callback

    REGISTER_POINTER(ReflectionTestComponent, Pointer, DummyClass*, true); // pointer object
    REGISTER_POINTER_CALLBACK(ReflectionTestComponent, PointerCallback, DummyClass*, true, OnPointerReflect); // pointer object callback

    REGISTER_ENUM(ReflectionTestComponent, Enum, entity::ColliderType); // enum
    REGISTER_ENUM_CALLBACK(ReflectionTestComponent, EnumCallback, entity::ColliderType, OnEnumReflect); // enum callback
}
//
// Created by Akira Mujawar on 04/02/26.
//

#include "reflection_test_component.hpp"
#include "entt_reflection_wrapper.hpp"

void MeowEngine::entity::ReflectionTestComponent::Reflect() {
    REGISTER_PROPERTY(ReflectionTestComponent, Data, DummyClass);
    REGISTER_ENUM(ReflectionTestComponent, Type, entity::ColliderType);
}

MeowEngine::entity::ReflectionTestComponent::ReflectionTestComponent()
: Data()
, Type (entity::ColliderType::SPHERE){
    Data.RootChildPointer = new ChildClass();
    Data.RootChildPointer->ChildSubPointer = new SubChildClass();
    Data.RootChild.ChildSubPointer = new SubChildClass();

    Data.BasicClassNonNull = new BasicClass();
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
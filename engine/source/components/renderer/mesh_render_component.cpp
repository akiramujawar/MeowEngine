//
// Created by Akira Mujawar on 23/06/24.
//

#include "mesh_render_component.hpp"
#include <log.hpp>
#include "entt_reflection_wrapper.hpp"

using MeowEngine::entity::MeshRenderComponent;

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
    REGISTER_PROPERTY(ChildClass, ChildSubPointer, SubChildClass*);

    MeowEngine::Reflection.Reflect<SubChildClass>();
}

void MeowEngine::entity::DummyClass::Reflect() {
//    MeowEngine::Reflection.Reflect<ChildClass>();
//    MeowEngine::Reflection.Reflect<DummyClass>();

    REGISTER_PROPERTY(DummyClass, RootMeshType, int);
    REGISTER_PROPERTY(DummyClass, RootSize, float);

    REGISTER_PROPERTY(DummyClass, RootChild, ChildClass);
    REGISTER_PROPERTY(DummyClass, RootChildPointer, ChildClass*);
    REGISTER_PROPERTY(DummyClass, RootText, PString);

    REGISTER_POINTER(DummyClass, BasicClassNull, BasicClass*, false);
    REGISTER_POINTER(DummyClass, BasicClassNonNull, BasicClass*, false);
}

void MeowEngine::entity::MeshRenderComponent::Reflect() {
    REGISTER_PROPERTY(MeshRenderComponent, Data, DummyClass);

    MeowEngine::Log("Reflected", "MeshRenderComponent");
}

MeshRenderComponent::MeshRenderComponent(MeowEngine::assets::ShaderPipelineType shader, MeowEngine::StaticMeshInstance *meshInstance)
    : MeshInstance(meshInstance), Data() {
    Shader = shader;

    Data.RootChildPointer = new ChildClass();
    Data.RootChildPointer->ChildSubPointer = new SubChildClass();
    Data.RootChild.ChildSubPointer = new SubChildClass();
    
    Data.BasicClassNonNull = new BasicClass();
}
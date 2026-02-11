//
// Created by Akira Mujawar on 30/08/24.
//

#include "box_collider_data.hpp"

#include "reflection_macro_wrapper.hpp"

using namespace MeowEngine::entity;

void BoxColliderData::Reflect() {
    REGISTER_PROPERTY_CALLBACK(BoxColliderData, Size, MeowEngine::math::Vector3, true, true, OnSizeReflect)
    REGISTER_PROPERTY_CALLBACK(BoxColliderData, StaticFriction, float, true, true, OnMaterialReflect)
    REGISTER_PROPERTY_CALLBACK(BoxColliderData, DynamicFriction, float, true, true, OnMaterialReflect)
    REGISTER_PROPERTY_CALLBACK(BoxColliderData, Restitution, float, true, true, OnMaterialReflect)

    REGISTER_PROPERTY(BoxColliderData, Geometry, physx::PxBoxGeometry, false, false)
    REGISTER_POINTER(BoxColliderData, Material, physx::PxMaterial*, false, false)
    REGISTER_POINTER(BoxColliderData, Shape, physx::PxShape*, false, false)
}

BoxColliderData::BoxColliderData()
: Material(nullptr)
, Shape(nullptr)
, Geometry() {
    Type = MeowEngine::entity::ColliderType::BOX;
    Size = MeowEngine::math::Vector3(0.5f, 0.5f, 0.5f);
    StaticFriction = 0.6f;
    DynamicFriction = 0.6f;
    Restitution = 0.6f;
}

BoxColliderData::BoxColliderData(const MeowEngine::math::Vector3& inSize)
: Material(nullptr)
, Shape(nullptr)
, Geometry() {
    Type = MeowEngine::entity::ColliderType::BOX;
    Size = inSize;
    StaticFriction = 0.6f;
    DynamicFriction = 0.6f;
    Restitution = 0.6f;
}

physx::PxGeometry& BoxColliderData::GetGeometry() {
    return Geometry;
}

physx::PxMaterial& BoxColliderData::GetMaterial() {
    return *Material;
}

physx::PxShape& BoxColliderData::GetShape() {
    return *Shape;
}

void BoxColliderData::CreateGeometry() {
    Geometry = physx::PxBoxGeometry(physx::PxVec3(Size.X, Size.Y, Size.Z));
}

void BoxColliderData::CreateMaterial(physx::PxPhysics* pPhysics) {
    Material = pPhysics->createMaterial(StaticFriction, DynamicFriction, Restitution);
}

void BoxColliderData::CreateShape(physx::PxPhysics* pPhysics) {
    Shape = pPhysics->createShape(Geometry, *Material);
}

// ----------------------

void BoxColliderData::OnSizeReflect() {
    Geometry.halfExtents = physx::PxVec3(Size.X / 2, Size.Y / 2, Size.Z / 2);

    // TODO: Find better a way to do this in a better way. As Shape is not available in other threads &
    // TODO: we would like to make it visible in UI but
    // TODO: somehow still keep in accessible for modifications on other threads
    if(Shape != nullptr) {
        Shape->setGeometry(Geometry);
        MeowEngine::Log("OnSizeReflect", "Reflected");
    }
}

void BoxColliderData::OnMaterialReflect() {
    MeowEngine::Log("OnMaterialReflect", "Reflected");
}

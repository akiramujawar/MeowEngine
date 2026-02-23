//
// Created by Akira Mujawar on 30/08/24.
//

#include "box_collider_shape.hpp"

#include "reflection_macro_wrapper.hpp"

using namespace MeowEngine::entity;

void BoxColliderShape::Reflect() {
    REGISTER_PROPERTY_CALLBACK(BoxColliderShape, Size, MeowEngine::math::Vector3, true, true, OnSizeReflect)
    REGISTER_PROPERTY_CALLBACK(BoxColliderShape, StaticFriction, float, true, true, OnMaterialReflect)
    REGISTER_PROPERTY_CALLBACK(BoxColliderShape, DynamicFriction, float, true, true, OnMaterialReflect)
    REGISTER_PROPERTY_CALLBACK(BoxColliderShape, Restitution, float, true, true, OnMaterialReflect)

    REGISTER_PROPERTY(BoxColliderShape, Geometry, physx::PxBoxGeometry, false, false)
    REGISTER_POINTER(BoxColliderShape, Material, physx::PxMaterial*, false, false)
    REGISTER_POINTER(BoxColliderShape, Shape, physx::PxShape*, false, false)
}

BoxColliderShape::BoxColliderShape()
: Material(nullptr)
, Shape(nullptr)
, Geometry() {
    Type = MeowEngine::entity::ColliderType::BOX;
    Size = MeowEngine::math::Vector3(0.5f, 0.5f, 0.5f);
    StaticFriction = 0.6f;
    DynamicFriction = 0.6f;
    Restitution = 0.3f;
}

BoxColliderShape::BoxColliderShape(const MeowEngine::math::Vector3& inSize)
: Material(nullptr)
, Shape(nullptr)
, Geometry() {
    Type = MeowEngine::entity::ColliderType::BOX;
    Size = inSize;
    StaticFriction = 0.6f;
    DynamicFriction = 0.6f;
    Restitution = 0.6f;
}

physx::PxGeometry& BoxColliderShape::GetGeometry() {
    return Geometry;
}

physx::PxMaterial& BoxColliderShape::GetMaterial() {
    return *Material;
}

physx::PxShape& BoxColliderShape::GetShape() {
    return *Shape;
}

void BoxColliderShape::CreateGeometry() {
    Geometry = physx::PxBoxGeometry(physx::PxVec3(Size.X, Size.Y, Size.Z));
}

void BoxColliderShape::CreateMaterial(physx::PxPhysics* pPhysics) {
    Material = pPhysics->createMaterial(StaticFriction, DynamicFriction, Restitution);
}

void BoxColliderShape::CreateShape(physx::PxPhysics* pPhysics) {
    Shape = pPhysics->createShape(Geometry, *Material);
}

// ----------------------

void BoxColliderShape::OnSizeReflect() {
    Geometry.halfExtents = physx::PxVec3(Size.X / 2, Size.Y / 2, Size.Z / 2);

    // TODO: Find better a way to do this in a better way. As Shape is not available in other threads &
    // TODO: we would like to make it visible in UI but
    // TODO: somehow still keep in accessible for modifications on other threads
    if(Shape != nullptr) {
        Shape->setGeometry(Geometry);
        MeowEngine::Log("OnSizeReflect", "Reflected");
    }
}

void BoxColliderShape::OnMaterialReflect() {
    MeowEngine::Log("OnMaterialReflect", "Reflected");
}

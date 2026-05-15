//
// Created by Akira Mujawar on 12/02/25.
//

#include "sphere_collider_shape.hpp"

#include "reflection_macro_wrapper.hpp"

namespace MeowEngine::entity {
    void SphereColliderShape::Reflect() {
        REGISTER_PROPERTY_CALLBACK(SphereColliderShape, Radius, float, true, true, OnRadiusReflect)
        REGISTER_PROPERTY_CALLBACK(SphereColliderShape, StaticFriction, float, true, true, OnMaterialReflect)
        REGISTER_PROPERTY_CALLBACK(SphereColliderShape, DynamicFriction, float, true, true, OnMaterialReflect)
        REGISTER_PROPERTY_CALLBACK(SphereColliderShape, Restitution, float, true, true, OnMaterialReflect)

        REGISTER_PROPERTY(SphereColliderShape, Geometry, physx::PxSphereGeometry, false, false)
        REGISTER_POINTER(SphereColliderShape, Material, physx::PxMaterial*, false, false)
        REGISTER_POINTER(SphereColliderShape, Shape, physx::PxShape*, false, false)
    }

    SphereColliderShape::SphereColliderShape()
            : Material(nullptr)
            , Shape(nullptr)
            , Geometry() {
        Type = MeowEngine::entity::ColliderType::SPHERE;
        Radius = 0.5f;
        StaticFriction = 1;
        DynamicFriction = 1;
        Restitution = 1;

    }

    SphereColliderShape::SphereColliderShape(float inRadius)
            : Material(nullptr)
            , Shape(nullptr)
            , Geometry() {
        Type = MeowEngine::entity::ColliderType::SPHERE;
        Radius = inRadius;
        StaticFriction = 1;
        DynamicFriction = 1;
        Restitution = 0.3f;
    }

    physx::PxGeometry& SphereColliderShape::GetGeometry() {
        return Geometry;
    }

    physx::PxMaterial& SphereColliderShape::GetMaterial() {
        return *Material;
    }

    physx::PxShape& SphereColliderShape::GetShape() {
        return *Shape;
    }

    void SphereColliderShape::CreateGeometry() {
        Geometry = physx::PxSphereGeometry(Radius);
    }

    void SphereColliderShape::CreateMaterial(physx::PxPhysics* pPhysics) {
        Material = pPhysics->createMaterial(StaticFriction, DynamicFriction, Restitution);
    }

    void SphereColliderShape::CreateShape(physx::PxPhysics* pPhysics) {
        Shape = pPhysics->createShape(Geometry, *Material);
    }

// ----------------------

    void SphereColliderShape::OnRadiusReflect() {
        Geometry.radius = Radius / 2;

        // TODO: Find better a way to do this in a better way. As Shape is not available in other threads &
        // TODO: we would like to make it visible in UI but
        // TODO: somehow still keep in accessible for modifications on other threads
        if(Shape != nullptr) {
            Shape->setGeometry(Geometry);
            MeowEngine::Log("OnSizeReflect", "Reflected");
        }
    }

    void SphereColliderShape::OnMaterialReflect() {
        MeowEngine::Log("OnMaterialReflect", "Reflected");
    }

} // MeowEngine
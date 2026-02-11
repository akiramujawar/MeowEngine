//
// Created by Akira Mujawar on 12/02/25.
//

#include "sphere_collider_data.hpp"

#include "reflection_macro_wrapper.hpp"

namespace MeowEngine::entity {
    void SphereColliderData::Reflect() {
        REGISTER_PROPERTY_CALLBACK(SphereColliderData, Radius, float, true, true, OnRadiusReflect)
        REGISTER_PROPERTY_CALLBACK(SphereColliderData, StaticFriction, float, true, true, OnMaterialReflect)
        REGISTER_PROPERTY_CALLBACK(SphereColliderData, DynamicFriction, float, true, true, OnMaterialReflect)
        REGISTER_PROPERTY_CALLBACK(SphereColliderData, Restitution, float, true, true, OnMaterialReflect)

        REGISTER_PROPERTY(SphereColliderData, Geometry, physx::PxSphereGeometry, false, false)
        REGISTER_POINTER(SphereColliderData, Material, physx::PxMaterial*, false, false)
        REGISTER_POINTER(SphereColliderData, Shape, physx::PxShape*, false, false)
    }

    SphereColliderData::SphereColliderData()
            : Material(nullptr)
            , Shape(nullptr)
            , Geometry() {
        Type = MeowEngine::entity::ColliderType::SPHERE;
        Radius = 0.5f;
        StaticFriction = 0.6f;
        DynamicFriction = 0.6f;
        Restitution = 0.6f;

    }

    SphereColliderData::SphereColliderData(float inRadius)
            : Material(nullptr)
            , Shape(nullptr)
            , Geometry() {
        Type = MeowEngine::entity::ColliderType::SPHERE;
        Radius = inRadius;
        StaticFriction = 0.6f;
        DynamicFriction = 0.6f;
        Restitution = 0.6f;
    }

    physx::PxGeometry& SphereColliderData::GetGeometry() {
        return Geometry;
    }

    physx::PxMaterial& SphereColliderData::GetMaterial() {
        return *Material;
    }

    physx::PxShape& SphereColliderData::GetShape() {
        return *Shape;
    }

    void SphereColliderData::CreateGeometry() {
        Geometry = physx::PxSphereGeometry(Radius);
    }

    void SphereColliderData::CreateMaterial(physx::PxPhysics* pPhysics) {
        Material = pPhysics->createMaterial(StaticFriction, DynamicFriction, Restitution);
    }

    void SphereColliderData::CreateShape(physx::PxPhysics* pPhysics) {
        Shape = pPhysics->createShape(Geometry, *Material);
    }

// ----------------------

    void SphereColliderData::OnRadiusReflect() {
        Geometry.radius = Radius / 2;

        // TODO: Find better a way to do this in a better way. As Shape is not available in other threads &
        // TODO: we would like to make it visible in UI but
        // TODO: somehow still keep in accessible for modifications on other threads
        if(Shape != nullptr) {
            Shape->setGeometry(Geometry);
            MeowEngine::Log("OnSizeReflect", "Reflected");
        }
    }

    void SphereColliderData::OnMaterialReflect() {
        MeowEngine::Log("OnMaterialReflect", "Reflected");
    }

} // MeowEngine
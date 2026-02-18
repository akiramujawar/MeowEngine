//
// Created by Akira Mujawar on 12/02/25.
//

#ifndef MEOWENGINE_SPHERE_COLLIDER_DATA_HPP
#define MEOWENGINE_SPHERE_COLLIDER_DATA_HPP

#include "collider_data.hpp"

namespace MeowEngine::entity {

    class SphereColliderData : public entity::ColliderData {
    public:
        REFLECT_MObject(SphereColliderData)
        static void Reflect();

        // using explicit prevents any implicit conerstion / copy-init
        // SphereColliderData data = 0 // error
        // SphereColliderData data(); // success
        explicit SphereColliderData();
        explicit SphereColliderData(float inRadius);
        virtual ~SphereColliderData() = default;

        physx::PxGeometry& GetGeometry() override;
        physx::PxMaterial& GetMaterial() override;
        physx::PxShape& GetShape() override;

        void CreateGeometry() override;
        void CreateMaterial(physx::PxPhysics*) override;
        void CreateShape(physx::PxPhysics*) override;

    private:
        void OnRadiusReflect();
        void OnMaterialReflect();

    public:
        float Radius;
        float StaticFriction;
        float DynamicFriction;
        float Restitution;

    private:
        physx::PxSphereGeometry Geometry;
        physx::PxMaterial* Material;
        physx::PxShape* Shape;
    };

} // MeowEngine

#endif //MEOWENGINE_SPHERE_COLLIDER_DATA_HPP

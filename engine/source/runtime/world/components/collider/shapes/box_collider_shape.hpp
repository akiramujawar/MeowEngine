//
// Created by Akira Mujawar on 30/08/24.
//

#ifndef MEOWENGINE_BOX_COLLIDER_SHAPE_HPP
#define MEOWENGINE_BOX_COLLIDER_SHAPE_HPP

#include "collider_shape_base.hpp"
#include "math_wrapper.hpp"

namespace MeowEngine::entity {
    class BoxColliderShape : public entity::ColliderShapeBase {
    public:
        REFLECT_MObject(BoxColliderShape)
        static void Reflect();

        // using explicit prevents any implicit conversion / copy-init
        // BoxColliderData data = 0; // error
        // BoxColliderData data(); // success
        explicit BoxColliderShape();
        explicit BoxColliderShape(const MeowEngine::math::Vector3& inSize);
        virtual ~BoxColliderShape() = default;

        physx::PxGeometry& GetGeometry() override;
        physx::PxMaterial& GetMaterial() override;
        physx::PxShape& GetShape() override;

        void CreateGeometry() override;
        void CreateMaterial(physx::PxPhysics*) override;
        void CreateShape(physx::PxPhysics*) override;

    private:
        void OnSizeReflect();
        void OnMaterialReflect();

    public:
        MeowEngine::math::Vector3 Size; // could a different class
        float StaticFriction;
        float DynamicFriction;
        float Restitution;

    private:
        physx::PxBoxGeometry Geometry;
        physx::PxMaterial* Material;
        physx::PxShape* Shape;
    };
}


#endif //MEOWENGINE_BOX_COLLIDER_SHAPE_HPP

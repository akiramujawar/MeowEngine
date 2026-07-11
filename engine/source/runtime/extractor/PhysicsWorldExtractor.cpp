//
// Created by Akira Mujawar on 05/07/26.
//

#include "PhysicsWorldExtractor.hpp"

#include "AssetManager.hpp"
#include "Hierarchy.hpp"
#include "Components.hpp"
#include "World.hpp"
#include "Rigidbody.hpp"
#include "Collider.hpp"
#include "MeowService.hpp"

namespace MeowEngine::Runtime {

    // loop through ecs registries
    // select root entites
    // if has rigidobody procces
    // if doesn't have rigidoby ignore
    // for editor tests (check for free colliders and throw error)

    // if has rigidboy process
    // - CreateRigidbodyCommand
    // - go through childs
    // - check for colliders and collect
    // - for editor tests (check for rigidobdies and throw error)


    void PhysicsWorldExtractor::Extract(Asset::World& world, Physics::PhysicsWorldData& data) {
        // BodyComponent
        // BoxComponent
        // SphereComponent

        // create rigidbody
        // -> assign entity handle guid
        // create collider
        // -> assign entity handle guid
        // -> setup the gemoetry by type

        // easy to check in reverse
        auto& ecs = world.GetRegistry();
        auto view = ecs.view<IdentityComponent, HierarchyComponent, Transform3DComponent, RigidbodyComponent>();

        for (auto &&entity : view) {
            auto&& [identity, hierarchy, transform, rigidbody] = view.get(entity);
            Physics::Rigidbody body { identity.GetGUIDInt(), rigidbody.Type };
            body.Position = transform.GetPosition();
            body.Quaternion = transform.GetQuaternion();
            // TODO: check for parent if any rigidbody exists, if so we detatch

            FindColliders(world, data, hierarchy.FirstChild, body);

            // push rigidbody
            data.RigidBodies.push_back(body);
        }

    }

    void PhysicsWorldExtractor::FindColliders(
        Asset::World& world ,
        Physics::PhysicsWorldData& data,
        EntityHandle child,
        Physics::Rigidbody& body
    ) {
        // first child
        // next child
        // next chil etc...
        // send child first child

        // for each rigidbody collect all child colliders
        while (child.GetIsValid()) {
            auto& hierarchy = world.GetComponent<HierarchyComponent>(child);
            auto [isValid, collider, material] = GetColliderData(world, child);

            if (isValid) {
                collider.RootObjectID = body.ObjectID;

                // track collider
                data.Colliders.push_back(collider);
                data.Materials.push_back(material);

                // add colliders to rigidbody &
                body.ColliderIDs.push_back(collider.ObjectID);
            }

            // inside
            FindColliders(world, data, hierarchy.FirstChild, body);

            // next child
            child = hierarchy.NextChildOfParent;
        }
    }

    std::tuple<bool, Physics::Collider, Physics::PhysicsMaterial> PhysicsWorldExtractor::GetColliderData(
        Asset::World& world,
        EntityHandle handle
    ) {
        auto& childIdentity = world.GetComponent<IdentityComponent>(handle);
        ColliderComponent* colliderBase = nullptr;
        Physics::Collider collider = {};

        collider.ObjectID = childIdentity.GetGUIDInt();

        // box
        if (world.HasComponent<BoxColliderComponent>(handle)) {
            auto& comp = world.GetComponent<BoxColliderComponent>(handle);
            collider.Type = Physics::ColliderType::BOX;
            colliderBase = &comp;
            collider.Geometry.Cube.HalfExtents = comp.HalfExtents;
        }

        // sphere
        if (world.HasComponent<SphereColliderComponent>(handle)) {
            auto& comp = world.GetComponent<SphereColliderComponent>(handle);
            collider.Type = Physics::ColliderType::SPHERE;
            colliderBase = &comp;
            collider.Geometry.Sphere.Radius = comp.Radius;
        }

        // capsule
        if (world.HasComponent<CapsuleColliderComponent>(handle)) {
            auto& comp = world.GetComponent<CapsuleColliderComponent>(handle);
            collider.Type = Physics::ColliderType::CAPSULE;
            colliderBase = &comp;
            collider.Geometry.Capsule.Radius = comp.Radius;
            collider.Geometry.Capsule.Height = comp.Height;
        }

        // mesh
        if (world.HasComponent<MeshColliderComponent>(handle)) {
            auto& comp = world.GetComponent<MeshColliderComponent>(handle);
            collider.Type = Physics::ColliderType::MESH;
            colliderBase = &comp;
        }

        // grab material asset
        Physics::PhysicsMaterial material;
        if (colliderBase) {
            auto& assetManager = MeowService().AssetManager;
            auto materialHandle = colliderBase->GetMaterialAssetHandle();
            auto* materialAsset = assetManager.GetAssetOrLoad<Asset::PhysicsMaterialAsset>(materialHandle);
            material = {
                materialHandle.GetUUID(),
                materialAsset->DynamicFriction,
                materialAsset->Restitution,
                materialAsset->StaticFriction
            };

            // track materials
            collider.MaterialID = materialHandle.GetUUID();

            return std::make_tuple(true, collider, material);
        }

        return std::make_tuple(false, collider, material);
    }
}

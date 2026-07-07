//
// Created by Akira Mujawar on 05/07/26.
//

#include "PhysicsWorldExtractor.hpp"

#include "Hierarchy.hpp"
#include "Components.hpp"
#include "World.hpp"
#include "Rigidbody.hpp"
#include "Collider.hpp"

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
        auto view = ecs.view<IdentityComponent, HierarchyComponent, RigidbodyComponent>();

        for (auto &&entity : view) {
            auto&& [identity, hierarchy, rigidbody] = view.get(entity);
            Physics::Rigidbody body { identity.GetGUIDInt() };
            data.Rigidbodies.push_back(body);

            // TODO: check for parent if any rigidbody exists, if so we detatch

            auto child = hierarchy.FirstChild;
            while (child.GetIsValid()) {
                auto& childIdentity = world.GetComponent<IdentityComponent>(child);
                Physics::Collider collider = {};
                collider.ObjectID = childIdentity.GetGUIDInt();

                // plane
                if (world.HasComponent<PlaneColliderComponent>(child)) {
                    auto& comp = world.GetComponent<PlaneColliderComponent>(child);
                    collider.RootObjectID = identity.GetGUIDInt();
                    collider.ObjectID = childIdentity.GetGUIDInt();
                    collider.Type = Physics::ColliderType::PLANE;
                }

                // box
                if (world.HasComponent<BoxColliderComponent>(child)) {
                    auto& comp = world.GetComponent<BoxColliderComponent>(child);
                    collider.RootObjectID = identity.GetGUIDInt();
                    collider.ObjectID = childIdentity.GetGUIDInt();
                    collider.Type = Physics::ColliderType::BOX;
                }

                // sphere
                if (world.HasComponent<SphereColliderComponent>(child)) {
                    auto& comp = world.GetComponent<SphereColliderComponent>(child);
                    collider.RootObjectID = identity.GetGUIDInt();
                    collider.ObjectID = childIdentity.GetGUIDInt();
                    collider.Type = Physics::ColliderType::SPHERE;
                }

                // capsule
                if (world.HasComponent<CapsuleColliderComponent>(child)) {
                    auto& comp = world.GetComponent<CapsuleColliderComponent>(child);
                    collider.RootObjectID = identity.GetGUIDInt();
                    collider.ObjectID = childIdentity.GetGUIDInt();
                    collider.Type = Physics::ColliderType::CAPSULE;
                }

                // child
                if (world.HasComponent<MeshColliderComponent>(child)) {
                    auto& comp = world.GetComponent<MeshColliderComponent>(child);
                    collider.RootObjectID = identity.GetGUIDInt();
                    collider.ObjectID = childIdentity.GetGUIDInt();
                    collider.Type = Physics::ColliderType::MESH;
                }

                data.Colliders.push_back(collider);
            }
        }

    }
}

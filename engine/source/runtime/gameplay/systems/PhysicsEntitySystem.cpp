//
// Created by Akira Mujawar on 30/06/26.
//

#include "PhysicsEntitySystem.hpp"

#include "RigidbodyComponent.hpp"
#include "World.hpp"

namespace MeowEngine::Runtime {
    void PhysicsEntitySystem::ProcessDirtyEntities(Asset::World& world) {
        const auto& dirtyChanges = world.GetDirtyEntities();

        // check for all add / remove operations on entities
        // with physics components only
        for (const auto& dirtyChange : dirtyChanges) {
            switch (dirtyChange.ComponentType) {
                case EntityComponentHash<RigidbodyComponent>(): {
                    break;
                }
                default: ;
            }
        }

        // let start with basic
        // on game start
        // create a command to start simulating physics
        // now do we create commands for every item or
        // do we do something like PhysicsExtract
        // ideally once we come into the live world we don't really need PhysicsExtract because ideally we will handle things through
        // Main Commands to Physics
        // & buffer<PhysicsResult> to Main

        // so any colliders mandatory requires rigid body
        // rigidbody can be static or dynamic and then later add kinematic

        // physx world inside physix module
        // or
        // what about physics world
        // PhysicsModule
        // -> owns PhysicsWorld
        // -> owns unique_ptr<IPhysicsSystem>
        // PhysXSystem extends IPhysicsSystem

        // how is gameplay system going to sync with physics system?
        // physicsSyncSystem on start
        // will create command to clear the PhysicsWorld




        // PhysicsExtractor => convets world for for physis start with
        // RenderEditorExtractor => converts like gizmos, grid, editor texture handles etc..
        // RenderPhyiscsExtractors => converts colliders, bounding boxes etc..
        // RenderEditorUIExtractor => converts required ui elements to popupate on ui
        // RenderGameplayExtractor => converts meshes, textures etc..
        // RenderGameplayUIExtractor => converts required ui elements to popup on ui active world

        // these mess have
        // EntityID => object id
        // Entity => object id for runtime (created by entt)
        // EntityHandle => collection of object id, object id (entity id, entity)
        // EntityComponent = object id but extended with entt
        // EntityRegistry => uses object id for entt registry => never expose

        // AssetHandle
        // guid => object id

        // object id => valid & guid => core
        // EntityHandle => runtime only
        // => EntityID => entt representation
        // => ObjectID => guid & validity
        // EntityID => entt represetnation => runtime only
        //



    }
}

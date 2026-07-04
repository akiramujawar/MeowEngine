//
// Created by Akira Mujawar on 04/07/26.
//

#include "ChangeEntityHierarchy.hpp"

#include "GameplaySystem.hpp"
#include "HierarchyComponent.hpp"
#include "MessageInitData.hpp"

namespace MeowEngine::Messaging {

    void ChangeEntityHierarchy::Execute(MessageInitData& context) {
        auto& world = context.Gameplay->GetWorld();

        // - Check if same
        if (MoveEntity.GetGUID() == IntoEntity.GetGUID()) {
            return;
        }

        world.Hierarchy.DetachParent(world, MoveEntity);
        world.Hierarchy.Reset(world, MoveEntity);
        world.Hierarchy.AttachParent(world, MoveEntity, IntoEntity);
    }

}

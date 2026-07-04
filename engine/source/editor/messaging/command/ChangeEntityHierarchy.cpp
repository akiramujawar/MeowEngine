//
// Created by Akira Mujawar on 04/07/26.
//

#include "ChangeEntityHierarchy.hpp"

#include "GameplaySystem.hpp"
#include "HierarchyComponent.hpp"
#include "MessageInitData.hpp"
#include "Hierarchy.hpp"

namespace MeowEngine::Messaging {

    void ChangeEntityHierarchy::Execute(MessageInitData& context) {
        auto& world = context.Gameplay->GetWorld();

        // - Check if same
        if (MoveEntity.GetGUID() == IntoEntity.GetGUID()) {
            return;
        }

        if (MoveEntity.GetIsValid()) {
            Runtime::Hierarchy::DetachParent(world, MoveEntity);
            Runtime::Hierarchy::Reset(world, MoveEntity);
        }

        if (MoveEntity.GetIsValid() && IntoEntity.GetIsValid()) {
            Runtime::Hierarchy::AttachParent(world, MoveEntity, IntoEntity);
        }
    }

}

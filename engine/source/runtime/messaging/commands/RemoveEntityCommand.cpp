//
// Created by Akira Mujawar on 03/07/26.
//

#include "RemoveEntityCommand.hpp"

#include "GameplaySystem.hpp"
#include "MessageInitData.hpp"
#include "Selector.hpp"

namespace MeowEngine::Messaging {

    void RemoveEntityCommand::Execute(MessageInitData& context) {
        auto& world = context.Gameplay->GetWorld();

        // NOTE: only for editor
        context.Selector->SelectedEntities.clear();
        context.Selector->SelectedEntity = Runtime::EntityHandle::Invalid();

        // remove
        world.RemoveEntity(Handle.GetGUID());
    }

}

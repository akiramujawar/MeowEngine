//
// Created by Akira Mujawar on 10/06/26.
//

#include <SelectEntityCommand.hpp>

#include <MessageInitData.hpp>
#include <Selector.hpp>
#include <GameplaySystem.hpp>

namespace MeowEngine::Messaging {

    void SelectEntityCommand::Execute(MessageInitData& context) {
        auto& world = context.Gameplay->GetWorld();
        auto entity = world.GetEntity(GUID);

        if (!IsCtrlSelect) {
            context.Selector->SelectedEntities.clear();
        }

        context.Selector->SelectedEntities.push_back(entity);
    }

}

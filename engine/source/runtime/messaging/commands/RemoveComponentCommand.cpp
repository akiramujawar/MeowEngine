//
// Created by Akira Mujawar on 03/07/26.
//

#include "RemoveComponentCommand.hpp"

#include "GameplaySystem.hpp"
#include "MessageInitData.hpp"
#include "reflection_macro_wrapper.hpp"

namespace MeowEngine::Messaging {

    void RemoveComponentCommand::Execute(MessageInitData& context) {
        auto compCallback = GetReflection().GetRemoveComponentCallback(ComponentToAddName);
        auto& world = context.Gameplay->GetWorld();
        compCallback(world, Handle);
    }

}
//
// Created by Akira Mujawar on 29/06/26.
//

#include "AddComponentCommand.hpp"

#include "GameplaySystem.hpp"
#include "MessageInitData.hpp"
#include "reflection_macro_wrapper.hpp"

namespace MeowEngine::Messaging {

    void AddComponentCommand::Execute(MessageInitData& context) {
        auto compCallback = GetReflection().GetAddComponentCallback(ComponentToAddName);
        auto& world = context.Gameplay->GetWorld();

        compCallback(world, Handle);
    }

}

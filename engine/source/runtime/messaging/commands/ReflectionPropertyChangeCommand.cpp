//
// Created by Akira Mujawar on 12/06/26.
//

#include <ReflectionPropertyChangeCommand.hpp>

#include <reflection_macro_wrapper.hpp>
#include <GameplaySystem.hpp>
#include <MessageInitData.hpp>

namespace MeowEngine::Messaging {
    ReflectionPropertyChangeCommand::ReflectionPropertyChangeCommand(MeowEngine::ReflectionPropertyChange* change) {
        Change = change;
    }

    void ReflectionPropertyChangeCommand::Execute(MessageInitData& context) {
        auto& world = context.Gameplay->GetWorld();
        auto& ecs = world.GetRegistry();
        // auto handle = world.FindHandle(static_cast<Runtime::EntityID>(Change->GUID));

        GetReflection().ApplyPropertyChange(*Change, Change->Handle, ecs);
    }

}

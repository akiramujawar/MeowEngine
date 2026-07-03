//
// Created by Akira Mujawar on 03/07/26.
//

#ifndef MEOWENGINE_REMOVECOMPONENTCOMMAND_HPP
#define MEOWENGINE_REMOVECOMPONENTCOMMAND_HPP


#include <Public/Messaging/Include.hpp>

#include "EntityHandle.hpp"

namespace MeowEngine::Messaging {
    class RemoveComponentCommand : public ICommand {
    public:
        RemoveComponentCommand(const Runtime::EntityHandle& handle, const std::string& componentToAddName) {
            Handle = handle;
            ComponentToAddName = componentToAddName;
        }

        void Execute(MessageInitData& context) override;

    private:
        Runtime::EntityHandle Handle;
        std::string ComponentToAddName;
    };
}


#endif //MEOWENGINE_REMOVECOMPONENTCOMMAND_HPP
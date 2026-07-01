//
// Created by Akira Mujawar on 29/06/26.
//

#ifndef MEOWENGINE_ADDCOMPONENTCOMMAND_HPP
#define MEOWENGINE_ADDCOMPONENTCOMMAND_HPP


#include <Public/Messaging/Include.hpp>

#include "EntityHandle.hpp"

namespace MeowEngine::Messaging {
    class AddComponentCommand : public ICommand {
    public:
        AddComponentCommand(const Runtime::EntityHandle& handle, const std::string& componentToAddName) {
            Handle = handle;
            ComponentToAddName = componentToAddName;
        }

        void Execute(MessageInitData& context) override;

    private:
        Runtime::EntityHandle Handle;
        std::string ComponentToAddName;
    };
}



#endif //MEOWENGINE_ADDCOMPONENTCOMMAND_HPP
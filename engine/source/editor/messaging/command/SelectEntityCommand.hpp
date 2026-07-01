//
// Created by Akira Mujawar on 10/06/26.
//

#ifndef MEOWENGINE_SELECTENTITYCOMMAND_HPP
#define MEOWENGINE_SELECTENTITYCOMMAND_HPP

#include <cstdint>
#include <Public/Messaging/Include.hpp>
#include "EntityHandle.hpp"

namespace MeowEngine::Messaging {
    class SelectEntityCommand : public ICommand {
    public:
        SelectEntityCommand(Runtime::EntityHandle handle, bool bIsCtrlSelect) {
            Handle = handle;
            IsCtrlSelect = bIsCtrlSelect;
        }

        void Execute(MessageInitData& context) override;

    private:
        Runtime::EntityHandle Handle;
        bool IsCtrlSelect;
    };
}


#endif //MEOWENGINE_SELECTENTITYCOMMAND_HPP
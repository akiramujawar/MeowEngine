//
// Created by Akira Mujawar on 10/06/26.
//

#ifndef MEOWENGINE_SELECTENTITYCOMMAND_HPP
#define MEOWENGINE_SELECTENTITYCOMMAND_HPP

#include <cstdint>
#include <Public/Messaging/Include.hpp>

namespace MeowEngine::Messaging {
    class SelectEntityCommand : public ICommand {
    public:
        SelectEntityCommand(uint32_t guid, bool bIsCtrlSelect) {
            GUID = guid;
            IsCtrlSelect = bIsCtrlSelect;
        }

        void Execute(MessageInitData& context) override;

    private:
        uint32_t GUID;
        bool IsCtrlSelect;
    };
}


#endif //MEOWENGINE_SELECTENTITYCOMMAND_HPP
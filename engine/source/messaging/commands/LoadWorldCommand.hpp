//
// Created by Akira Mujawar on 18/06/26.
//

#ifndef MEOWENGINE_LOADWORLDCOMMAND_HPP
#define MEOWENGINE_LOADWORLDCOMMAND_HPP

#include <string>

#include "Public/Messaging/Include.hpp"
#include "AssetHandle.hpp"

namespace MeowEngine::Messaging {
    class LoadWorldCommand : public ICommand {
    public:
        LoadWorldCommand(const Asset::AssetHandle& handle) {
            WorldHandle = handle;
        }

        void Execute(MessageInitData& context) override;

    private:
        Asset::AssetHandle WorldHandle;
    };
}



#endif //MEOWENGINE_LOADWORLDCOMMAND_HPP
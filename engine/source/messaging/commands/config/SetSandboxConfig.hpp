//
// Created by Akira Mujawar on 29/06/26.
//

#ifndef MEOWENGINE_SETSANDBOXCONFIG_HPP
#define MEOWENGINE_SETSANDBOXCONFIG_HPP


#include <Public/Messaging/Include.hpp>
#include "AssetHandle.hpp"

namespace MeowEngine::Messaging {
    class SetSandboxConfig : public ICommand {
    public:
        SetSandboxConfig(const Asset::AssetHandle& worldLaunchHandle) {
            WorldLaunchHandle = worldLaunchHandle;
        }

        void Execute(MessageInitData& context) override;

    private:
        Asset::AssetHandle WorldLaunchHandle;
    };
}




#endif //MEOWENGINE_SETSANDBOXCONFIG_HPP
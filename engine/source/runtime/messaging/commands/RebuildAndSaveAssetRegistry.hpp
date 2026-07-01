//
// Created by Akira Mujawar on 17/06/26.
//

#ifndef MEOWENGINE_REBUILDANDSAVEASSETREGISTRY_HPP
#define MEOWENGINE_REBUILDANDSAVEASSETREGISTRY_HPP

#include <Public/Messaging/Include.hpp>
#include <Public/Core/Include.hpp>

namespace MeowEngine::Messaging {
    class RebuildAndSaveAssetRegistry : public ICommand {
    public:
        RebuildAndSaveAssetRegistry() = default;

        void Execute(MessageInitData& context) override;
    };
}


#endif //MEOWENGINE_REBUILDANDSAVEASSETREGISTRY_HPP
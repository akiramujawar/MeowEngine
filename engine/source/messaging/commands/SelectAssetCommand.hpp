//
// Created by Akira Mujawar on 12/06/26.
//

#ifndef MEOWENGINE_SELECTASSETCOMMAND_HPP
#define MEOWENGINE_SELECTASSETCOMMAND_HPP


#include <Public/Messaging/Include.hpp>
#include <Public/Core.hpp>

namespace MeowEngine::Messaging {
    class SelectAssetCommand  : public ICommand {
    public:
        SelectAssetCommand(String path) {
            Path = path;
        }

        void Execute(MessageContext& context) override;

    private:
        String Path;
    };
}


#endif //MEOWENGINE_SELECTASSETCOMMAND_HPP
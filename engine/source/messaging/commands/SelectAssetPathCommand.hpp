//
// Created by Akira Mujawar on 12/06/26.
//

#ifndef MEOWENGINE_SELECTASSETPATHCOMMAND_HPP
#define MEOWENGINE_SELECTASSETPATHCOMMAND_HPP


#include <Public/Messaging/Include.hpp>
#include <Public/Core/Include.hpp>

namespace MeowEngine::Messaging {
    class SelectAssetPathCommand  : public ICommand {
    public:
        SelectAssetPathCommand(String path) {
            Path = path;
        }

        void Execute(MessageInitData& context) override;

    private:
        String Path;
    };
}


#endif //MEOWENGINE_SELECTASSETPATHCOMMAND_HPP
//
// Created by Akira Mujawar on 12/06/26.
//

#ifndef MEOWENGINE_SELECTDIRECTORYPATHCOMMAND_HPP
#define MEOWENGINE_SELECTDIRECTORYPATHCOMMAND_HPP

#include <Public/Messaging/Include.hpp>
#include <Public/Core/Include.hpp>

namespace MeowEngine::Messaging {
    class SelectDirectoryPathCommand  : public ICommand {
    public:
        SelectDirectoryPathCommand(String path) {
            Path = path;
        }

        void Execute(MessageInitData& context) override;

    private:
        String Path;
    };
}

#endif //MEOWENGINE_SELECTDIRECTORYPATHCOMMAND_HPP
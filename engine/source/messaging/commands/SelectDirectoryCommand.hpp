//
// Created by Akira Mujawar on 12/06/26.
//

#ifndef MEOWENGINE_SELECTDIRECTORYCOMMAND_HPP
#define MEOWENGINE_SELECTDIRECTORYCOMMAND_HPP

#include <Public/Messaging/Include.hpp>
#include <Public/Core.hpp>

namespace MeowEngine::Messaging {
    class SelectDirectoryCommand  : public ICommand {
    public:
        SelectDirectoryCommand(String path) {
            Path = path;
        }

        void Execute(MessageContext& context) override;

    private:
        String Path;
    };
}

#endif //MEOWENGINE_SELECTDIRECTORYCOMMAND_HPP
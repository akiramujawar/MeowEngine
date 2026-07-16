//
// Created by Akira Mujawar on 16/07/26.
//

#ifndef MEOWENGINE_RENAMEFILECOMMAND_HPP
#define MEOWENGINE_RENAMEFILECOMMAND_HPP


#include <string>

#include <Public/Messaging/Include.hpp>
#include "Public/Core/Include.hpp"

namespace MeowEngine::Messaging {
    class RenameFileCommand : public ICommand {
    public:
        RenameFileCommand(const String& filePath, const String& name) {
            FilePath = filePath;
            Name = name;
        }

        void Execute(MessageInitData& context) override;

    private:
        String FilePath;
        String Name;
    };
}


#endif //MEOWENGINE_RENAMEFILECOMMAND_HPP
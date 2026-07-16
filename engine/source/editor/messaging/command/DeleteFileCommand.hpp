//
// Created by Akira Mujawar on 16/07/26.
//

#ifndef MEOWENGINE_DELETEFILECOMMAND_HPP
#define MEOWENGINE_DELETEFILECOMMAND_HPP


#include <Public/Messaging/Include.hpp>
#include "Public/Core/Include.hpp"

namespace MeowEngine::Messaging {
    class DeleteFileCommand : public ICommand {
    public:
        DeleteFileCommand(const String& filePath) {
            FilePath = filePath;
        }

        void Execute(MessageInitData& context) override;

    private:
        String FilePath;
    };
}


#endif //MEOWENGINE_DELETEFILECOMMAND_HPP
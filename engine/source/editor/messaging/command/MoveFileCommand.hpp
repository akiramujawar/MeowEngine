//
// Created by Akira Mujawar on 16/07/26.
//

#ifndef MEOWENGINE_MOVEASSETCOMMAND_HPP
#define MEOWENGINE_MOVEASSETCOMMAND_HPP


#include <string>

#include <Public/Messaging/Include.hpp>
#include "Public/Core/Include.hpp"

namespace MeowEngine::Messaging {
    class MoveFileCommand : public ICommand {
    public:
        MoveFileCommand(const String& filePath, const String& moveToPath) {
            FilePath = filePath;
            MoveToPath = moveToPath;
        }

        void Execute(MessageInitData& context) override;

    private:
        String FilePath;
        String MoveToPath;
    };
}


#endif //MEOWENGINE_MOVEASSETCOMMAND_HPP
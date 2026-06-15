//
// Created by Akira Mujawar on 12/06/26.
//

#ifndef MEOWENGINE_IMPORTFILECOMMAND_HPP
#define MEOWENGINE_IMPORTFILECOMMAND_HPP

#include <Public/Messaging/Include.hpp>
#include <string>

namespace MeowEngine::Messaging {
    class ImportFileCommand : public ICommand {
    public:
        ImportFileCommand(const std::string& importFolderPath) {
            ImportFolderPath = importFolderPath;
        }

        void Execute(MessageInitData& context) override;

    private:
        std::string ImportFolderPath;
    };
}


#endif //MEOWENGINE_IMPORTFILECOMMAND_HPP
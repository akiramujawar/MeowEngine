//
// Created by Akira Mujawar on 12/06/26.
//

#ifndef MEOWENGINE_IMPORTFILECOMMAND_HPP
#define MEOWENGINE_IMPORTFILECOMMAND_HPP

#include <string>

#include <Public/Messaging/Include.hpp>
#include "AssetImportType.hpp"


namespace MeowEngine::Messaging {
    class ImportFileCommand : public ICommand {
    public:
        ImportFileCommand(const std::string& importToFolderPath, Asset::AssetImportType type) {
            ImportToFolderPath = importToFolderPath;
            Type = type;
        }

        void Execute(MessageInitData& context) override;

    private:
        std::string ImportToFolderPath;
        Asset::AssetImportType Type;
    };
}


#endif //MEOWENGINE_IMPORTFILECOMMAND_HPP
//
// Created by Akira Mujawar on 12/06/26.
//

#include <SelectDirectoryCommand.hpp>

#include <MessageInitData.hpp>
#include <Selector.hpp>

namespace MeowEngine::Messaging {

    void SelectDirectoryCommand::Execute(MessageInitData& context) {
        context.Selector->SelectedDirectoryPath = Path.GetRawString();
    }

}

//
// Created by Akira Mujawar on 12/06/26.
//

#include <SelectDirectoryCommand.hpp>

#include <MessageContext.hpp>
#include <Selector.hpp>

namespace MeowEngine::Messaging {

    void SelectDirectoryCommand::Execute(MessageContext& context) {
        context.Selector->SelectedDirectoryPath = Path.GetRawString();
    }

}

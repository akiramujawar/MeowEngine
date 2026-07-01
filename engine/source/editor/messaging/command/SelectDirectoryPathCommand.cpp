//
// Created by Akira Mujawar on 12/06/26.
//

#include <SelectDirectoryPathCommand.hpp>

#include <MessageInitData.hpp>
#include <Selector.hpp>

namespace MeowEngine::Messaging {

    void SelectDirectoryPathCommand::Execute(MessageInitData& context) {
        context.Selector->SelectedDirectoryPath = Path.GetRawString();

        MeowEngine::Log("Directory Selected: ", Path.GetRawString());
    }

}

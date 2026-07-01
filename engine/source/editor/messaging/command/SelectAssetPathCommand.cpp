//
// Created by Akira Mujawar on 12/06/26.
//

#include <SelectAssetPathCommand.hpp>

#include <MessageInitData.hpp>
#include <Selector.hpp>

namespace MeowEngine::Messaging {

    void SelectAssetPathCommand::Execute(MessageInitData& context) {
        context.Selector->SelectedAssetPath = Path.GetRawString();

        MeowEngine::Log("Asset Selected: ", Path.GetRawString());
    }

}
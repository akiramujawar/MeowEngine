//
// Created by Akira Mujawar on 12/06/26.
//

#include <SelectAssetCommand.hpp>

#include <MessageInitData.hpp>
#include <Selector.hpp>

namespace MeowEngine::Messaging {

    void SelectAssetCommand::Execute(MessageInitData& context) {
        context.Selector->SelectedAssetPath = Path.GetRawString();
    }

}
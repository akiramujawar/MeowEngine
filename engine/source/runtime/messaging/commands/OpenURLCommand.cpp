//
// Created by Akira Mujawar on 29/06/26.
//

#include "OpenURLCommand.hpp"

#include "GraphicsDevice.hpp"
#include "LoadWorldCommand.hpp"

#include "MessageInitData.hpp"


namespace MeowEngine::Messaging {

    void OpenUrlCommand::Execute(MessageInitData& context) {
        context.Device->GetWindow().OpenURL(URL);
    }

}


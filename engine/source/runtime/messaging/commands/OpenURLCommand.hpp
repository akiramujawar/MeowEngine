//
// Created by Akira Mujawar on 29/06/26.
//

#ifndef MEOWENGINE_OPENURLCOMMAND_HPP
#define MEOWENGINE_OPENURLCOMMAND_HPP

#include <utility>

#include "Public/Messaging/Include.hpp"
#include "Public/Core/Include.hpp"

namespace MeowEngine::Messaging {
    class OpenUrlCommand : public ICommand {
    public:
        OpenUrlCommand(WebAddress url) : URL(std::move(url)) {}

        void Execute(MessageInitData& context) override;

    private:
        WebAddress URL;
    };
}


#endif //MEOWENGINE_OPENURLCOMMAND_HPP
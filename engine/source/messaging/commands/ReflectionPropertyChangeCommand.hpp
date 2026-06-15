//
// Created by Akira Mujawar on 12/06/26.
//

#ifndef MEOWENGINE_REFLECTIONPROPERTYCHANGECOMMAND_HPP
#define MEOWENGINE_REFLECTIONPROPERTYCHANGECOMMAND_HPP

#include <Public/Messaging/Include.hpp>

namespace MeowEngine {
    class ReflectionPropertyChange;
}

namespace MeowEngine::Messaging {
    class ReflectionPropertyChangeCommand : public ICommand {
    public:
        ReflectionPropertyChangeCommand(MeowEngine::ReflectionPropertyChange* change);

        void Execute(MessageInitData& context) override;

    private:
        ReflectionPropertyChange* Change;
    };
}


#endif //MEOWENGINE_REFLECTIONPROPERTYCHANGECOMMAND_HPP
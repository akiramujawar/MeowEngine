//
// Created by Akira Mujawar on 04/07/26.
//

#include <Public/Messaging/Include.hpp>

#ifndef MEOWENGINE_CHANGEENTITYHIERARCHYCOMMAND_HPP
#define MEOWENGINE_CHANGEENTITYHIERARCHYCOMMAND_HPP

#include "EntityHandle.hpp"

namespace MeowEngine::Messaging {

    class ChangeEntityHierarchyCommand : public ICommand {
    public:
        ChangeEntityHierarchyCommand(Runtime::EntityHandle move, Runtime::EntityHandle into) {
            MoveEntity = move;
            IntoEntity = into;
        }

        void Execute(MessageInitData& context) override;

    private:
        Runtime::EntityHandle MoveEntity;
        Runtime::EntityHandle IntoEntity;
    };

}


#endif //MEOWENGINE_CHANGEENTITYHIERARCHYCOMMAND_HPP
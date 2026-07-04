//
// Created by Akira Mujawar on 04/07/26.
//

#include <Public/Messaging/Include.hpp>

#ifndef MEOWENGINE_CHANGEENTITYHIERARCHY_HPP
#define MEOWENGINE_CHANGEENTITYHIERARCHY_HPP

#include "EntityHandle.hpp"

namespace MeowEngine::Messaging {

    class ChangeEntityHierarchy : public ICommand {
    public:
        ChangeEntityHierarchy(Runtime::EntityHandle move, Runtime::EntityHandle into) {
            MoveEntity = move;
            IntoEntity = into;
        }

        void Execute(MessageInitData& context) override;

    private:
        Runtime::EntityHandle MoveEntity;
        Runtime::EntityHandle IntoEntity;
    };

}


#endif //MEOWENGINE_CHANGEENTITYHIERARCHY_HPP
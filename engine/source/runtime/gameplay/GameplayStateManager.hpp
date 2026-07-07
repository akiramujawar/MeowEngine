//
// Created by Akira Mujawar on 06/07/26.
//

#ifndef MEOWENGINE_GAMEPLAYSTATEMANAGER_HPP
#define MEOWENGINE_GAMEPLAYSTATEMANAGER_HPP

#include "GameplayStateContext.hpp"

#include "GameplayState.hpp"

namespace MeowEngine::Runtime {
    class GameplayStateManager {
    public:
        GameplayStateManager() = default;
        ~GameplayStateManager() = default;

        void Init(const GameplayStateContext& context);

        void SwitchState(GameplayState state);

    private:
        GameplayStateContext Context {};
    };
}


#endif //MEOWENGINE_GAMEPLAYSTATEMANAGER_HPP
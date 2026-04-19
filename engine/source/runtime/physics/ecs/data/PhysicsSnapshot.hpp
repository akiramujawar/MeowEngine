//
// Created by Akira Mujawar on 18/04/26.
//

#ifndef MEOWENGINE_PHYSICSSNAPSHOT_HPP
#define MEOWENGINE_PHYSICSSNAPSHOT_HPP

#include <vector>
#include <Rigidbody.hpp>

namespace MeowEngine::Runtime {
    struct PhysicsSnapshot {
        std::vector<int32_t> Added;
        std::vector<int32_t> Removed;
        std::vector<Rigidbody> Updated;
    };
}

#endif //MEOWENGINE_PHYSICSSNAPSHOT_HPP
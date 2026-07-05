//
// Created by Akira Mujawar on 01/09/24.
//

#ifndef MEOWENGINE_COLLIDER_SHAPE_TYPE_HPP
#define MEOWENGINE_COLLIDER_SHAPE_TYPE_HPP

namespace MeowEngine::Runtime {

//    REFLECT_ENUM(MeowEngine::entity, ColliderType);
    enum class ColliderType {
        BOX,
        SPHERE,
        CAPSULE,
        MESH
    }; REFLECT_ENUM(MeowEngine::Runtime, ColliderType);

}


#endif //MEOWENGINE_COLLIDER_SHAPE_TYPE_HPP

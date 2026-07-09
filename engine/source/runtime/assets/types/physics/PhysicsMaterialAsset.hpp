//
// Created by Akira Mujawar on 09/07/26.
//

#ifndef MEOWENGINE_PHYSICSMATERIALASSET_HPP
#define MEOWENGINE_PHYSICSMATERIALASSET_HPP

#include "IAsset.hpp"

namespace MeowEngine::Asset {
    class PhysicsMaterialAsset : public IAsset {
    public:
        float StaticFriction;
        float DynamicFriction;
        float Restitution;
    };
}

#endif //MEOWENGINE_PHYSICSMATERIALASSET_HPP
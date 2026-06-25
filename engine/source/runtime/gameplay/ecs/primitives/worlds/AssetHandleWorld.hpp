//
// Created by Akira Mujawar on 25/06/26.
//

#ifndef MEOWENGINE_ASSETHANDLEWORLD_HPP
#define MEOWENGINE_ASSETHANDLEWORLD_HPP


#include <World.hpp>

namespace MeowEngine::Runtime {
    class AssetHandleWorld : public Asset::World {
    public:
        AssetHandleWorld();
        ~AssetHandleWorld() override = default;

    private:
        void CreateCamera();
        void CreateEmtpy(const std::string& name);
    };
}


#endif //MEOWENGINE_ASSETHANDLEWORLD_HPP
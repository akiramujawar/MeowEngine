//
// Created by Akira Mujawar on 05/03/26.
//

#ifndef MEOWENGINE_ASSETMANAGER_HPP
#define MEOWENGINE_ASSETMANAGER_HPP

#include <AssetRegistry.hpp>

namespace MeowEngine::Runtime::Asset {
    class AssetManager {
    public:
        AssetManager();
        ~AssetManager();

        void Init();

        AssetRegistry& GetResolver();

    private:
        AssetRegistry Resolver;
    };
}


#endif //MEOWENGINE_ASSETMANAGER_HPP
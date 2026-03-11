//
// Created by Akira Mujawar on 05/03/26.
//

#ifndef MEOWENGINE_ASSETMANAGER_HPP
#define MEOWENGINE_ASSETMANAGER_HPP

#include <AssetResolver.hpp>

namespace MeowEngine::Runtime::Asset {
    class AssetManager {
    public:
        AssetManager();
        ~AssetManager();

        AssetResolver& GetResolver();

    private:
        AssetResolver Resolver;
    };
}


#endif //MEOWENGINE_ASSETMANAGER_HPP
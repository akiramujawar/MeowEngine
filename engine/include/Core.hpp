//
// Created by Akira Mujawar on 24/02/26.
//

#ifndef MEOWENGINE_CORE_HPP
#define MEOWENGINE_CORE_HPP

#include "Object.hpp"
#include "String.hpp"
#include "Name.hpp"
#include "WebAddress.hpp"

#include <Engine.hpp>
#include <AssetManager.hpp>

namespace MeowEngine {
    namespace Types = Core::Types;

    using Core::Types::Object;
    using Core::Types::String;
    using Core::Types::Name;
    using Core::Types::WebAddress;

    inline Runtime::Asset::AssetManager& AssetManagerTemp() {
        return Engine::Get().GetAssetManager();
    }

}

#endif //MEOWENGINE_CORE_HPP

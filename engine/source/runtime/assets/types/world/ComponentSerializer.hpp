//
// Created by Akira Mujawar on 17/06/26.
//

#ifndef MEOWENGINE_COMPONENTSERIALIZER_HPP
#define MEOWENGINE_COMPONENTSERIALIZER_HPP

#include <string>

#include "Public/IO/Forward.hpp"

namespace MeowEngine::Asset {
    class ComponentSerializer {
    public:
        static void Serialize(Serialization::Serializer& serializer, void* instance, const std::string& className);
        static void Deserialize(Serialization::Serializer& serializer, void* instance, const std::string& className);
    };
}


#endif //MEOWENGINE_COMPONENTSERIALIZER_HPP
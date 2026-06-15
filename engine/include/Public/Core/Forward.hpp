//
// Created by Akira Mujawar on 15/06/26.
//

#ifndef MEOWENGINE_COREF_HPP
#define MEOWENGINE_COREF_HPP

namespace MeowEngine {
    namespace Core::Types {
        struct String;
        class Name;
        struct WebAddress;
        class Object;
    }

    using Core::Types::Object;
    using Core::Types::String;
    using Core::Types::Name;
    using Core::Types::WebAddress;

    namespace Core::IO::FileSystem {
        class Path;
    }

    using Core::IO::FileSystem::Path;
}

#endif //MEOWENGINE_COREF_HPP
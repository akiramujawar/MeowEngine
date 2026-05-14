//
// Created by Akira Mujawar on 14/05/26.
//

#ifndef MEOWENGINE_IRENDERAPI_HPP
#define MEOWENGINE_IRENDERAPI_HPP

namespace MeowEngine::Rendering {
    class IRenderAPI {
    public:
        virtual ~IRenderAPI() = default;
        virtual void Clear() = 0;
    };
}

#endif //MEOWENGINE_IRENDERAPI_HPP
//
// Created by Akira Mujawar on 14/05/26.
//

#ifndef MEOWENGINE_GLRENDERAPI_HPP
#define MEOWENGINE_GLRENDERAPI_HPP

#include <IRenderAPI.hpp>

namespace MeowEngine::Rendering {
    class GLRender : public IRenderAPI {
    public:
        explicit GLRender();
        ~GLRender() override;

        void Clear() override;
    };
}


#endif //MEOWENGINE_GLRENDERAPI_HPP
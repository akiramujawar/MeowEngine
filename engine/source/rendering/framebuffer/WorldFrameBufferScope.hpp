//
// Created by Akira Mujawar on 25/06/26.
//

#ifndef MEOWENGINE_WORLDFRAMEBUFFERSCOPE_HPP
#define MEOWENGINE_WORLDFRAMEBUFFERSCOPE_HPP

#include <ISceneFrameBuffer.hpp>

namespace MeowEngine::Rendering {
    /**
     * RAII pattern (resource acquisition is initialisation)
     */
    class WorldFrameBufferScope {
    public:
        WorldFrameBufferScope(ISceneFrameBuffer& buffer);
        ~WorldFrameBufferScope();

    private:
        ISceneFrameBuffer& FrameBuffer;
    };
}


#endif //MEOWENGINE_WORLDFRAMEBUFFERSCOPE_HPP
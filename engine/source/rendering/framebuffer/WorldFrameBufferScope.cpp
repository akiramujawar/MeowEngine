//
// Created by Akira Mujawar on 25/06/26.
//

#include "WorldFrameBufferScope.hpp"

namespace MeowEngine::Rendering {
    WorldFrameBufferScope::WorldFrameBufferScope(ISceneFrameBuffer& buffer)
        : FrameBuffer(buffer) {
        FrameBuffer.Bind();
    }

    WorldFrameBufferScope::~WorldFrameBufferScope() {
        FrameBuffer.Unbind();
    }
}

//
// Created by Akira Mujawar on 14/05/26.
//

#ifndef MEOWENGINE_RENDERCOMMAND_HPP
#define MEOWENGINE_RENDERCOMMAND_HPP

#include <memory>

#include <IRenderAPI.hpp>
#include <GraphicsType.hpp>

namespace MeowEngine::Rendering {
    /**
     * Used to execute render command on device (like clear, draw mesh, etc...)
     */
    class RenderCommand {
    public:
        static void Init(GraphicsType type);

        // frame buffer stuff
        static void Clear();
        static ISceneFrameBuffer& GetSceneFrameBuffer();

    private:
        static std::unique_ptr<IRenderAPI> Command;
    };
}

#endif //MEOWENGINE_RENDERCOMMAND_HPP
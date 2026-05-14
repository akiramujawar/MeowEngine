//
// Created by Akira Mujawar on 14/05/26.
//

#ifndef MEOWENGINE_RENDERCOMMAND_HPP
#define MEOWENGINE_RENDERCOMMAND_HPP

#include <memory>

#include <IRenderAPI.hpp>
#include <GraphicsAPI.hpp>

namespace MeowEngine::Rendering {
    class RenderCommand {
    public:
        static void Init(GraphicsAPI type);
        static void Clear();

    private:
        static std::unique_ptr<IRenderAPI> Command;
    };
}

#endif //MEOWENGINE_RENDERCOMMAND_HPP
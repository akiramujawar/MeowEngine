//
// Created by Akira Mujawar on 22/06/24.
//

#ifndef MEOWENGINE_GLSKYBOXPIPELINE_HPP
#define MEOWENGINE_GLSKYBOXPIPELINE_HPP

#include <cstdint>
#include <IRenderPipeline.hpp>

namespace MeowEngine::Rendering {
    class SkyboxDrawData;

    class GLSkyboxPipeline : public IRenderPipeline {
    public:
        GLSkyboxPipeline();
        ~GLSkyboxPipeline() override;

        void Draw(RenderContext& context, SkyboxDrawData& data) const;

        // void Render(
        //     const MeowEngine::OpenGLAssetManager& assetManager,
        //     const MeowEngine::entity::SkyBoxComponent* renderComponent,
        //     const MeowEngine::PerspectiveCamera* camera
        // ) const;

    private:
        uint32_t VertexArrayID = 0;
    };
}

#endif //MEOWENGINE_GLSKYBOXPIPELINE_HPP

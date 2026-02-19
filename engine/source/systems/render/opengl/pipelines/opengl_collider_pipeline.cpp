//
// Created by Akira Mujawar on 04/02/25.
//

#include "opengl_collider_pipeline.hpp"
#include "transform3d_component.hpp"
#include "collider_component.hpp"
#include "opengl_extension.hpp"

namespace MeowEngine {

    OpenGLColliderPipeline::OpenGLColliderPipeline(const GLuint &inShaderProgramID)
    : ShaderProgramID(inShaderProgramID) {}

    OpenGLColliderPipeline::~OpenGLColliderPipeline() noexcept {}

    void OpenGLColliderPipeline::Render(MeowEngine::PerspectiveCamera* cameraObject, entt::registry& registry) {
        // Since physics runs on separate thread,
        // we access only the transform data from render buffer
        // & using its property component data we draw the collider
//        std::vector<glm::mat4> colliders;
        const glm::mat4 cameraMatrix {cameraObject->GetProjectionMatrix() * cameraObject->GetViewMatrix()};
        std::vector<glm::mat4> boxColliders;
        std::vector<glm::mat4> sphereColliders;

        for(auto &&[entity, transform, collider]: registry.view<entity::Transform3DComponent, entity::ColliderComponent>().each()) {
            math::Matrix4x4 rotationMatrix = transform.Quaternion.GetRotationMatrix4x4();

            glm::mat4 rotation4Matrix = MeowEngine::OpenGLExtension::GetMat4FromMatrix4x4(rotationMatrix);

            // cannot any more use transform matrix
            // we will take the position, rotation & pick size collider data & create our own transform matrix
            // this we can decouple and keep different sizes/positions
            // when building transform matrix,
            // position =transform position + collider offset
            // rotation = transform rotation
            // scale = transform scale * collider scale
            glm::mat4 transformMatrix =
                    cameraMatrix
                    * glm::translate(transform.IdentityMatrix, glm::vec3(transform.Position.X, transform.Position.Y, transform.Position.Z))
                    * rotation4Matrix;

            // get the colliders, cast as per the types and calculate their transform matrix
            // & segregate them into for instance rendering
            entity::ColliderShapeBase& data = collider.GetColliderData();

            switch (data.GetType()) {
                case entity::ColliderType::BOX: {
                    auto& shape = data.Cast<entity::BoxColliderShape>();

                    transformMatrix *= glm::scale(transform.IdentityMatrix, glm::vec3(transform.Scale.X * shape.Size.X, transform.Scale.Y * shape.Size.Y,transform.Scale.Z * shape.Size.Z));
                    boxColliders.push_back(transformMatrix);

                    break;
                }
                case entity::ColliderType::SPHERE: {
                    auto &shape = data.Cast<entity::SphereColliderShape>();
                    transformMatrix *= glm::scale(transform.IdentityMatrix, glm::vec3(transform.Scale.X * shape.Radius, transform.Scale.Y * shape.Radius, transform.Scale.Z * shape.Radius));
                    sphereColliders.push_back(transformMatrix);
                    break;
                }
                default:
                    break;
            }


        }

        glUseProgram(ShaderProgramID);
        glDisable(GL_CULL_FACE);
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID, "u_view"), 1, GL_FALSE, &cameraObject->GetViewMatrix()[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID, "u_projection"), 1, GL_FALSE, &cameraObject->GetProjectionMatrix()[0][0]);
#ifndef USING_GLES
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif

        BoxCollider.Draw(boxColliders);
        SphereCollider.Draw(sphereColliders);
    }
} // MeowEngine
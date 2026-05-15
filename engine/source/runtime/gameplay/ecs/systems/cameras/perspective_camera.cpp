//
// Created by Akira Mujawar on 12/09/22.
//

#include "perspective_camera.hpp"
#include "log.hpp"
using MeowEngine::PerspectiveCamera;

namespace {
    glm::mat4 CreateProjectionMatrix(const float& width, const float& height) {
        return glm::perspectiveLH_NO(glm::radians(45.0f), width / height, 0.01f, 3000.0f);
    }

    glm::mat4 CreateViewMatrix(glm::vec3 position, glm::vec3 lookAtTarget, glm::vec3 up) {
        return glm::lookAtRH(position, lookAtTarget, up);
    }
} // namespace

struct PerspectiveCamera::Internal {
    glm::vec3 Position;
    glm::vec3 Up;
    glm::vec3 LookAtTarget; //at what point the camera should look at
    glm::mat4 ProjectionMatrix;

    Internal(const float& width, const float& height)
        : ProjectionMatrix(CreateProjectionMatrix(width, height))
        , Position(0.0f, 1.0f , -10.0f)
        , LookAtTarget(0.0f, 1.0f, 0.0f)
        , Up(0.0f, 1.0f, 0.0f) {
    }
};

MeowEngine::PerspectiveCamera::PerspectiveCamera(const float &width, const float &height)
    :  InternalPointer(make_internal_ptr<Internal>(width, height)) {}

void PerspectiveCamera::Configure(const glm::vec3& position, const glm::vec3& up, const glm::vec3& direction) {
    InternalPointer->Position = position;
    InternalPointer->Up = up;
    InternalPointer->LookAtTarget = position + glm::vec3(direction.x, direction.y, direction.z);
}

const glm::mat4 MeowEngine::PerspectiveCamera::GetProjectionMatrix() const {
    return InternalPointer->ProjectionMatrix;
}

const glm::mat4 MeowEngine::PerspectiveCamera::GetViewMatrix() const {
    return ::CreateViewMatrix(InternalPointer->Position, InternalPointer->LookAtTarget, InternalPointer->Up);
}

const glm::vec3 MeowEngine::PerspectiveCamera::GetPosition() const {
    return InternalPointer->Position;
}

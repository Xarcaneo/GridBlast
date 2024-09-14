#pragma once

#include "ICameraService.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class CameraService : public ICameraService {
public:
    CameraService();

    // Get the view matrix (calculated from position, target, and up direction)
    glm::mat4 getViewMatrix() const override;

    // Set the camera's position
    void setPosition(const glm::vec3& newPosition) override;

    // Get the camera's position
    glm::vec3 getPosition() const override;

    // Set the camera's target
    void setTarget(const glm::vec3& newTarget) override;

    // Get the camera's target
    glm::vec3 getTarget() const override;

    // Move the camera in the world space
    void move(const glm::vec3& offset) override;

    void clampCameraToMapBounds(const glm::vec2& playerPosition, const glm::vec2& mapSize) override;

private:
    glm::vec3 position;  // Camera position in world space
    glm::vec3 target;    // The point the camera is looking at
    glm::vec3 upDirection; // The up direction of the camera (usually {0, 1, 0})
};

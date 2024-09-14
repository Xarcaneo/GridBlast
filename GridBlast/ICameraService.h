#pragma once

#include "IGameService.h"
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class ICameraService : public IGameService {
public:
    virtual ~ICameraService() override = default;

    // Get the view matrix (calculated from camera's position and orientation)
    virtual glm::mat4 getViewMatrix() const = 0;

    // Set the camera's position
    virtual void setPosition(const glm::vec3& position) = 0;

    // Get the camera's position
    virtual glm::vec3 getPosition() const = 0;

    // Set the camera's target (where the camera is looking)
    virtual void setTarget(const glm::vec3& target) = 0;

    // Get the camera's target
    virtual glm::vec3 getTarget() const = 0;

    // Move the camera in the world space
    virtual void move(const glm::vec3& offset) = 0;

    virtual void clampCameraToMapBounds(const glm::vec2& playerPosition, const glm::vec2& mapSize) = 0;
};

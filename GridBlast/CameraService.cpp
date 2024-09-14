#include "CameraService.h"
#include <glm/gtc/matrix_transform.hpp> // For glm::lookAt
#include "ServiceRegistry.h"
#include "IRenderService.h"

CameraService::CameraService()
    : position(0.0f, 0.0f, 3.0f), // Default position
    target(0.0f, 0.0f, 0.0f),   // Default target
    upDirection(0.0f, 1.0f, 0.0f) // Default up direction
{
}

// Get the view matrix (calculated from position, target, and up direction)
glm::mat4 CameraService::getViewMatrix() const {
    // Get the viewport size (width and height)
    auto renderService = ServiceRegistry::getInstance().getService<IRenderService>();
    glm::ivec2 viewportSize = renderService->getViewportSize();

    // Calculate the offset to center the camera on the player
    float offsetX = viewportSize.x / 2.0f;
    float offsetY = viewportSize.y / 2.0f;

    // Translate the world opposite to the player's position and apply the centering offset
    return glm::translate(glm::mat4(1.0f), glm::vec3(-position.x + offsetX, -position.y + offsetY, 0.0f));
}

void CameraService::clampCameraToMapBounds(const glm::vec2& playerPosition, const glm::vec2& mapSize) {
    auto renderService = ServiceRegistry::getInstance().getService<IRenderService>();
    glm::ivec2 viewportSize = renderService->getViewportSize(); // Screen size

    float halfScreenWidth = viewportSize.x / 2.0f;
    float halfScreenHeight = viewportSize.y / 2.0f;

    // Clamp the camera position to ensure it doesn't move beyond the map bounds
    float clampedX = glm::clamp(playerPosition.x, halfScreenWidth, mapSize.x - halfScreenWidth);
    float clampedY = glm::clamp(playerPosition.y, halfScreenHeight, mapSize.y - halfScreenHeight);

    setPosition(glm::vec3(clampedX, clampedY, position.z));
}

// Set the camera's position
void CameraService::setPosition(const glm::vec3& newPosition) {
    position = newPosition;
}

// Get the camera's position
glm::vec3 CameraService::getPosition() const {
    return position;
}

// Set the camera's target
void CameraService::setTarget(const glm::vec3& newTarget) {
    target = newTarget;
}

// Get the camera's target
glm::vec3 CameraService::getTarget() const {
    return target;
}

// Move the camera in the world space
void CameraService::move(const glm::vec3& offset) {
    position += offset;
    target += offset; // Optionally adjust this if you want to maintain the target.
}

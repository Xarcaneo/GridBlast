#include "RenderService.h"
#include <glm/ext/matrix_clip_space.hpp>
#include "ServiceRegistry.h"
#include "ICameraService.h"

// Get the projection matrix
glm::mat4 RenderService::getProjectionMatrix() const
{
    return projectionMatrix;
}

// Set the projection matrix
void RenderService::setProjectionMatrix(const glm::mat4& matrix)
{
    projectionMatrix = matrix;
}

// Get the tile size
glm::vec2 RenderService::getTileSize() const
{
    return tileSize;
}

// Set the tile size
void RenderService::setTileSize(const glm::vec2& size)
{
    tileSize = size;
}

// Get the viewport size (only width and height)
glm::ivec2 RenderService::getViewportSize() const
{
    return viewportSize;
}

// Set the viewport size (only width and height)
void RenderService::setViewportSize(const glm::ivec2& newViewportSize)
{
    viewportSize = newViewportSize;

    // Calculate the orthographic projection matrix for a 2D game
    projectionMatrix = glm::ortho(
        0.0f, static_cast<float>(viewportSize.x),   // Left and Right
        static_cast<float>(viewportSize.y), 0.0f,   // Bottom and Top (note: top is at 0 in OpenGL)
        -1.0f, 1.0f                                // Near and Far planes
    );
}

// Implementing window getter and setter
GLFWwindow* RenderService::getWindow() const {
    return window;
}

void RenderService::setWindow(GLFWwindow* newWindow) {
    window = newWindow;
}

// Get the view matrix
glm::mat4 RenderService::getViewMatrix() const {
    return viewMatrix;
}

// Set the view matrix
void RenderService::setViewMatrix(const glm::mat4& matrix) {
    viewMatrix = matrix;
}

// Inside RenderService or a suitable class
void RenderService::SetupMatricesForRendering(bool useCamera) {
    if (useCamera) {
        // Use the CameraService's matrices for gameplay
        auto cameraService = ServiceRegistry::getInstance().getService<ICameraService>();
        glm::mat4 view = cameraService->getViewMatrix();
        glm::mat4 projection = getProjectionMatrix();  // Already stored in RenderService
        setViewMatrix(view);
        setProjectionMatrix(projection);
    }
    else {
        // Use identity matrices for UI (menus, etc.)
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = getProjectionMatrix();  // Already stored in RenderService
        setViewMatrix(view);
        setProjectionMatrix(projection);
    }
}



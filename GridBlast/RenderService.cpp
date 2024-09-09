#include "RenderService.h"

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
}

// Implementing window getter and setter
GLFWwindow* RenderService::getWindow() const {
    return window;
}

void RenderService::setWindow(GLFWwindow* newWindow) {
    window = newWindow;
}
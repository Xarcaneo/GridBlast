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

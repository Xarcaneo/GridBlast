#pragma once

#include "IGameService.h"
#include <glm/mat4x4.hpp>  // Include GLM for mat4
#include <glm/vec2.hpp>    // Include GLM for vec2

class IRenderService : public IGameService
{
public:
    // Virtual destructor
    virtual ~IRenderService() override = default;

    // Virtual getter for projectionMatrix
    virtual glm::mat4 getProjectionMatrix() const = 0;

    // Virtual setter for projectionMatrix
    virtual void setProjectionMatrix(const glm::mat4& matrix) = 0;

    // Virtual getter for tileSize
    virtual glm::vec2 getTileSize() const = 0;

    // Virtual setter for tileSize
    virtual void setTileSize(const glm::vec2& size) = 0;

protected:
    glm::mat4 projectionMatrix;
    glm::vec2 tileSize; // Variable to store tile size
};

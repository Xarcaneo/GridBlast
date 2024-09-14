#pragma once

#include "IGameService.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>    // Include GLFW for window handling
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

    virtual glm::mat4 getViewMatrix() const = 0;            // New method to get the view matrix
    virtual void setViewMatrix(const glm::mat4& matrix) = 0; // New method to set the view matrix

    // Virtual getter for tileSize
    virtual glm::vec2 getTileSize() const = 0;

    // Virtual setter for tileSize
    virtual void setTileSize(const glm::vec2& size) = 0;

    // Virtual getter for viewport size
    virtual glm::ivec2 getViewportSize() const = 0;

    // Virtual setter for viewport size
    virtual void setViewportSize(const glm::ivec2& viewport) = 0;

    // Getter for GLFWwindow pointer
    virtual GLFWwindow* getWindow() const = 0;

    // Setter for GLFWwindow pointer
    virtual void setWindow(GLFWwindow* window) = 0;

    virtual void SetupMatricesForRendering(bool useCamera) = 0;

protected:
    glm::mat4 projectionMatrix;
    glm::vec2 tileSize;        // Variable to store tile size
    GLFWwindow* window = nullptr; // Pointer to the window (GLFWwindow)
    glm::mat4 viewMatrix;
    glm::ivec2 viewportSize;  // Stores only the viewport width and height
};

#pragma once

#include "IRenderService.h"

class RenderService : public IRenderService
{
public:
    RenderService() = default;
    ~RenderService() override = default;

    // Implement the virtual methods from IRenderService
    glm::mat4 getProjectionMatrix() const override;
    void setProjectionMatrix(const glm::mat4& matrix) override;

    glm::vec2 getTileSize() const override;
    void setTileSize(const glm::vec2& size) override;

    // Viewport related methods
    glm::ivec2 getViewportSize() const override;                // Get the viewport size {width, height}
    void setViewportSize(const glm::ivec2& viewport) override;  // Set the viewport size {width, height}

    glm::mat4 getViewMatrix() const override;              
    void setViewMatrix(const glm::mat4& matrix) override;

    GLFWwindow* getWindow() const override;
    void setWindow(GLFWwindow* window) override;

    void SetupMatricesForRendering(bool useCamera) override;
};


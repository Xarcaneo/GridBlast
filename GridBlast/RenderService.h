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
    glm::ivec2 getViewportSize() const;                // Get the viewport size {width, height}
    void setViewportSize(const glm::ivec2& viewport);  // Set the viewport size {width, height}

private:
    glm::mat4 projectionMatrix;
    glm::vec2 tileSize;
    glm::ivec2 viewportSize;  // Stores only the viewport width and height
};


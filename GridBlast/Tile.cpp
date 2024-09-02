#include "Tile.h"
#include "IRenderService.h"
#include "ServiceRegistry.h"

// Definition of the static SpriteRenderer
SpriteRenderer Tile::spriteRenderer;
bool Tile::isRendererInitialized = false; 

Tile::Tile(const Texture& texture, const glm::vec2& position, int row, int column,
    float rotate, const glm::vec3& color)
    : texture(texture), position(position), row(row), column(column), rotate(rotate), color(color) {
    // Initialize the renderer only once
    if (!isRendererInitialized) {
        InitializeRenderer();
        isRendererInitialized = true;
    }
}

void Tile::InitializeRenderer() {
    spriteRenderer.Initialize();
}

void Tile::Render() const {
    std::shared_ptr<IRenderService> retrievedRenderService = ServiceRegistry::getInstance().getService<IRenderService>();
    glm::vec2 tileSize = retrievedRenderService->getTileSize();
    spriteRenderer.Render(texture, position, tileSize, rotate, color, row, column);
}

glm::vec2 Tile::GetPosition() const {
    return position;
}
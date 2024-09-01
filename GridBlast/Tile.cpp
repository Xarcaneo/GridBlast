#include "Tile.h"
#include "GameConfig.h"

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
    glm::vec2 tileSize = GameConfig::GetTileSize(); // Get the global tile size
    spriteRenderer.Render(texture, position, tileSize, rotate, color, row, column);
}

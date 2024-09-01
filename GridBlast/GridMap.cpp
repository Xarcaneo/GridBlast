#include "GridMap.h"
#include "GameConfig.h"
#include "StaticTile.h"
#include <iostream>

GridMap::GridMap(int width, int height, ResourceManager& resourceManager)
    : width(width), height(height), resourceManager(resourceManager) {
    grid.resize(width);
    for (int x = 0; x < width; ++x) {
        grid[x].resize(height);
    }
}

void GridMap::Initialize() {
    // Retrieve the texture from the resource manager
    std::shared_ptr<Texture> texture = resourceManager.GetTexture("borderTiles");

    // Get the tile size from GameConfig
    glm::vec2 tileSize = GameConfig::GetTileSize();

    // Initialize the grid with tiles
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            glm::vec2 position = glm::vec2(x * tileSize.x, y * tileSize.y);
            // Use the texture and position to create a StaticTile
            grid[x][y] = std::make_unique<StaticTile>(*texture, position, 0, 0);
            std::cout << "Rendering Tile at position: (" << position.x << ", " << position.y << ")\n";
        }
    }
}


void GridMap::Render() const {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (grid[x][y]) {
                grid[x][y]->Render();
            }
        }
    }
}

Tile* GridMap::GetTile(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return grid[x][y].get();
    }
    return nullptr;
}

void GridMap::SetTile(int x, int y, std::unique_ptr<Tile> tile) {
    grid[x][y] = std::move(tile); // Correct: Transfers ownership of the unique_ptr
}


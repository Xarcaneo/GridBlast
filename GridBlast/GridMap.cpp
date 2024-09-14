#include "GridMap.h"
#include "StaticTile.h"
#include <iostream>
#include "IResourceService.h"
#include "IRenderService.h"
#include "ServiceRegistry.h"

GridMap::GridMap()
 {
    Initialize();
}

void GridMap::Initialize() {
    // Retrieve the texture from the resource manager
    std::shared_ptr<Texture> texture = ServiceRegistry::getInstance().getService<IResourceService>()->GetTexture("borderTiles");

    // Get the tile size from the render service
    std::shared_ptr<IRenderService> retrievedRenderService = ServiceRegistry::getInstance().getService<IRenderService>();
    glm::vec2 tileSize = retrievedRenderService->getTileSize();

    // Load the level using LevelLoader
    levelLoader.LoadLevel("D:/GitHub/GridBlast/Resource Files/Maps/map.json");

    // Initialize the grid
    width = levelLoader.getMapWidth();
    height = levelLoader.getMapHeight();
    grid.resize(width);
    for (int x = 0; x < width; ++x) {
        grid[x].resize(height);
    }

    // Populate the grid with tiles from the LevelLoader
    const auto& layers = levelLoader.getLayers();
    for (const auto& layer : layers) {
        for (const auto& tileData : layer.tiles) {
            glm::vec2 position = glm::vec2(tileData.position.x * tileSize.x, tileData.position.y * tileSize.y);
            // Use the texture and position to create a StaticTile based on the tile ID
            grid[tileData.position.x][tileData.position.y] = std::make_unique<StaticTile>(*texture, position, 0, tileData.id);
        }
    }

    // Set up the player (use a different position if needed)
    glm::vec2 playerPosition = glm::vec2(10, 10);
    player = std::make_unique<Player>(*texture, playerPosition, 10);
}


void GridMap::Render() const {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (grid[x][y]) {
                grid[x][y]->Render();
            }
        }
    }

    player->Render();
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

Player* GridMap::GetPlayer() const {
    return player.get();
}


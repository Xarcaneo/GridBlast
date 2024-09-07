#include "GridMap.h"
#include "StaticTile.h"
#include <iostream>
#include "IResourceService.h"
#include "IRenderService.h"
#include "ServiceRegistry.h"

GridMap::GridMap(int width, int height)
    : width(width), height(height)
 {
    grid.resize(width);
    for (int x = 0; x < width; ++x) {
        grid[x].resize(height);
    }

    Initialize();
}

void GridMap::Initialize() {
    // Retrieve the texture from the resource manager
    std::shared_ptr<Texture> texture = ServiceRegistry::getInstance().getService<IResourceService>()->GetTexture("borderTiles");

    // Get the tile size
    std::shared_ptr<IRenderService> retrievedRenderService = ServiceRegistry::getInstance().getService<IRenderService>();
    glm::vec2 tileSize = retrievedRenderService->getTileSize();

    // Initialize the grid with tiles
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            glm::vec2 position = glm::vec2(x * tileSize.x, y * tileSize.y);
            // Use the texture and position to create a StaticTile
            grid[x][y] = std::make_unique<StaticTile>(*texture, position, 0, 0);
        }
    }

    //std::shared_ptr<Texture> texture = resourceManager.GetTexture("borderTiles");
    glm::vec2 position = glm::vec2(10, 10);
    player = std::make_unique<Player>(*texture, position, 10);
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


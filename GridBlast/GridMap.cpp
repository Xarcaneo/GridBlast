// GridMap.cpp
#include "GridMap.h"
#include "StaticTile.h"
#include <iostream>
#include "IResourceService.h"
#include "IRenderService.h"
#include "ServiceRegistry.h"

GridMap::GridMap() {
    Initialize();
}

void GridMap::Initialize() {
    // Retrieve the texture from the resource manager
    std::shared_ptr<Texture> texture = ServiceRegistry::getInstance().getService<IResourceService>()->GetTexture("tileset");

    // Get the tile size from the render service
    std::shared_ptr<IRenderService> renderService = ServiceRegistry::getInstance().getService<IRenderService>();
    glm::vec2 tileSize = renderService->getTileSize();

    // Load the level using LevelLoader
    levelLoader.LoadLevel("../Resource Files/Maps/map.json");

    // Initialize the grid
    width = levelLoader.getMapWidth();
    height = levelLoader.getMapHeight();

    // Correctly resize the grid without copying unique_ptr
    grid.resize(width);
    for (int x = 0; x < width; ++x) {
        grid[x].resize(height);
    }

    // Get tile definitions
    const auto& tileDefs = levelLoader.getTileDefinitions();

    // Populate the grid with tiles from the LevelLoader
    const auto& layers = levelLoader.getLayers();
    for (const auto& layer : layers) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int tileID = layer.data[y][x];
                if (tileID == 0) continue; // No tile at this position

                auto it = tileDefs.find(tileID);
                if (it == tileDefs.end()) {
                    std::cerr << "Tile ID " << tileID << " not found in tile definitions.\n";
                    continue;
                }

                const auto& tileDef = it->second;
                glm::vec2 position = glm::vec2(x * tileSize.x, y * tileSize.y);

                // Create the tile
                auto tile = std::make_unique<StaticTile>(*texture, position, tileDef.row, tileDef.column);

                // Initialize the vector at grid[x][y] if it's empty
                if (grid[x][y].empty()) {
                    grid[x][y] = std::vector<std::unique_ptr<Tile>>();
                }

                // Add tile to the grid at this position
                grid[x][y].push_back(std::move(tile));
            }
        }
    }

    // Set up the player (use a different position if needed)
    glm::vec2 playerPosition = glm::vec2(1 * tileSize.x, 1 * tileSize.y);
    player = std::make_unique<Player>(*texture, playerPosition, 70);
}

void GridMap::Render() const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Render all tiles at this position in order
            for (const auto& tile : grid[x][y]) {
                tile->Render();
            }
        }
    }

    player->Render();
}

Tile* GridMap::GetTile(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        if (!grid[x][y].empty()) {
            // Return the topmost tile (last in the vector)
            return grid[x][y].back().get();
        }
    }
    return nullptr;
}

void GridMap::SetTile(int x, int y, std::unique_ptr<Tile> tile) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        grid[x][y].push_back(std::move(tile));
    }
}

Player* GridMap::GetPlayer() const {
    return player.get();
}

void GridMap::Update(float deltaTime) {
    player->Update(deltaTime);
}

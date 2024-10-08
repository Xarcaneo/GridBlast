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

    // Populate the grid and characters with tiles from the LevelLoader
    const auto& layers = levelLoader.getLayers();
    for (const auto& layer : layers) {
        if (layer.name != "Characters") {
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
                    auto tile = std::make_unique<StaticTile>(*texture, position, tileDef.row, tileDef.column, tileDef.collision);

                    // Initialize the vector at grid[x][y] if it's empty
                    if (grid[x][y].empty()) {
                        grid[x][y] = std::vector<std::unique_ptr<Tile>>();
                    }

                    // Add tile to the grid at this position
                    grid[x][y].push_back(std::move(tile));
                }
            }
        }
        else
        {
            // Handle character layer
            const auto& characterDefs = levelLoader.getCharacterDefinitions();

            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    int charID = layer.data[y][x];
                    if (charID == 0) continue; // No character at this position

                    // Check if character definition exists
                    auto charDefIt = characterDefs.find(charID);
                    if (charDefIt == characterDefs.end()) {
                        std::cerr << "Character ID " << charID << " not found in character definitions.\n";
                        continue;
                    }

                    const auto& charDef = charDefIt->second;
                    glm::vec2 characterPosition = glm::vec2(x * tileSize.x, y * tileSize.y);

                    if (charDef.type == "player") {
                        // Create the player at the found position
                        player = std::make_unique<Player>(*texture, characterPosition, charDef.speed);
                    }
                }
            }
        }
    }
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

    if(player)
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
    CheckCollisions();

    if (player)
        player->Update(deltaTime);
}

void GridMap::CheckCollisions()
{
    if (player) {
        glm::vec2 nextPosition = player->GetNextPosition();
        CheckCollisionAtNextPosition(nextPosition, *player);
    }
}

bool GridMap::CheckCollisionAtNextPosition(glm::vec2& nextPosition, Character& character) {
    int gridX = static_cast<int>(nextPosition.x);
    int gridY = static_cast<int>(nextPosition.y);

    // Ensure the next position is within bounds
    if (gridX >= 0 && gridX < width && gridY >= 0 && gridY < height) {
        const Tile* tile = GetTile(gridX, gridY);
        if (tile && tile->IsCollidable()) {
            character.StopMove();
            return true;
        }
    }

    return false;
}

#ifndef GRID_MAP_H
#define GRID_MAP_H

#include <vector>
#include <memory>
#include "Tile.h"
#include "ResourceManager.h"

class GridMap {
public:
    GridMap(int width, int height, ResourceManager& resourceManager);

    void Initialize(); // Initialize the grid with tiles
    void Render() const; // Render all tiles in the grid

    Tile* GetTile(int x, int y) const; // Get a tile at a specific grid position
    void SetTile(int x, int y, std::unique_ptr<Tile> tile); // Set a tile at a specific grid position

private:
    int width;
    int height;
    ResourceManager& resourceManager; // Reference to the resource manager
    std::vector<std::vector<std::unique_ptr<Tile>>> grid; // 2D grid of tiles
};

#endif // GRID_MAP_H

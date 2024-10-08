#ifndef GRID_MAP_H
#define GRID_MAP_H

#include <vector>
#include <memory>
#include "Player.h"
#include "Tile.h"
#include "LevelLoader.h"

class GridMap {
public:
    GridMap();

    void Initialize(); // Initialize the grid with tiles
    void Render() const; // Render all tiles in the grid

    Tile* GetTile(int x, int y) const; // Get a tile at a specific grid position
    void SetTile(int x, int y, std::unique_ptr<Tile> tile); // Set a tile at a specific grid position

    Player* GetPlayer() const; // Getter for the player instance

    int getMapWidth() const { return width; }
    int getMapHeight() const { return height; }

    void Update(float deltaTime);

private:
    void CheckCollisions();
    bool CheckCollisionAtNextPosition(glm::vec2& nextPosition, Character &character);

    int width;
    int height;
    std::vector<std::vector<std::vector<std::unique_ptr<Tile>>>> grid;
    std::unique_ptr<Player> player;        // Player instance

    LevelLoader levelLoader;
};

#endif // GRID_MAP_H

#pragma once
#include <string>
#include <vector>
#include <glm/vec2.hpp> // For 2D vectors
#include "json.hpp"

// Renamed the Tile struct to LevelTile to avoid conflict with the Tile class
struct LevelTile {
    int id;
    glm::vec2 position;
};

struct Layer {
    std::string name;
    std::vector<LevelTile> tiles;
    bool collider;
};

class LevelLoader {
public:
    LevelLoader() = default; // Default constructor

    // Load level from the specified file path
    void LoadLevel(const std::string& filePath);

    int getTileSize() const { return tileSize; }
    int getMapWidth() const { return mapWidth; }
    int getMapHeight() const { return mapHeight; }
    const std::vector<Layer>& getLayers() const { return layers; }

private:
    int tileSize;
    int mapWidth;
    int mapHeight;
    std::vector<Layer> layers;

    void parseJSON(const nlohmann::json& jsonData);
};

// LevelLoader.h
#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <glm/vec2.hpp>
#include "json.hpp"

struct TileDefinition {
    int id;
    std::string type;
    int row;
    int column;
};

struct Layer {
    std::string name;
    std::vector<std::vector<int>> data; // 2D array of tile IDs
};

class LevelLoader {
public:
    LevelLoader() = default;

    void LoadLevel(const std::string& filePath);

    int getMapWidth() const { return mapWidth; }
    int getMapHeight() const { return mapHeight; }
    const std::unordered_map<int, TileDefinition>& getTileDefinitions() const { return tileDefinitions; }
    const std::vector<Layer>& getLayers() const { return layers; }

private:
    int mapWidth;
    int mapHeight;
    std::unordered_map<int, TileDefinition> tileDefinitions;
    std::vector<Layer> layers;

    void parseJSON(const nlohmann::json& jsonData);
    void parseTileset(const nlohmann::json& tilesetData);
};

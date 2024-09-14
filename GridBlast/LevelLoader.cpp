#include "LevelLoader.h"
#include <fstream>

using json = nlohmann::json;

void LevelLoader::LoadLevel(const std::string& filePath) {
    // Open and read the JSON file
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open level file!");
    }

    // Parse the JSON file
    json jsonData;
    file >> jsonData;

    if (jsonData.is_discarded()) {
        throw std::runtime_error("Error parsing JSON file");
    }

    // Parse the JSON data
    parseJSON(jsonData);
}

void LevelLoader::parseJSON(const json& jsonData) {
    // Extract basic map information
    tileSize = jsonData["tileSize"].get<int>();
    mapWidth = jsonData["mapWidth"].get<int>();
    mapHeight = jsonData["mapHeight"].get<int>();

    // Parse the layers
    for (const auto& layerData : jsonData["layers"]) {
        Layer layer;
        layer.name = layerData["name"].get<std::string>();
        layer.collider = layerData["collider"].get<bool>();

        // Parse each tile in the layer
        for (const auto& tileData : layerData["tiles"]) {
            LevelTile tile;
            tile.id = std::stoi(tileData["id"].get<std::string>());
            tile.position = glm::vec2(tileData["x"].get<int>(), tileData["y"].get<int>());

            layer.tiles.push_back(tile);
        }

        layers.push_back(layer);
    }
}

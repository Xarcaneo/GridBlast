// LevelLoader.cpp
#include "LevelLoader.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

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
    mapWidth = jsonData["mapWidth"].get<int>();
    mapHeight = jsonData["mapHeight"].get<int>();

    // Parse the tileset
    parseTileset(jsonData["tileset"]);

    // Parse the layers
    for (const auto& layerData : jsonData["layers"]) {
        Layer layer;
        layer.name = layerData["name"].get<std::string>();
        layer.data = layerData["data"].get<std::vector<std::vector<int>>>();
        layers.push_back(layer);
    }
}

void LevelLoader::parseTileset(const json& tilesetData) {
    for (const auto& tile : tilesetData["tiles"]) {
        TileDefinition tileDef;
        tileDef.id = tile["id"].get<int>();
        tileDef.type = tile["type"].get<std::string>();
        tileDef.row = tile["row"].get<int>();
        tileDef.column = tile["column"].get<int>();
        tileDefinitions[tileDef.id] = tileDef;
    }
}

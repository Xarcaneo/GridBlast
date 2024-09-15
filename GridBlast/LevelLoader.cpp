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

    // Load the tileset file
    if (jsonData.contains("tileset")) {
        std::string tilesetFilePath = jsonData["tileset"].get<std::string>();
        LoadTileset(tilesetFilePath);
    }

    // Load the characterset 
    if (jsonData.contains("characterset")) {
        std::string characterFilePath = jsonData["characterset"];
        LoadCharacterSet(characterFilePath);
    }

    // Parse the JSON data
    parseJSON(jsonData);
}

void LevelLoader::parseJSON(const json& jsonData) {
    // Extract basic map information
    mapWidth = jsonData["mapWidth"].get<int>();
    mapHeight = jsonData["mapHeight"].get<int>();

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
        tileDef.collision = tile["collision"].get<bool>(); 

        tileDefinitions[tileDef.id] = tileDef;
    }
}

void LevelLoader::LoadTileset(const std::string& tilesetFilePath) {
    std::ifstream file(tilesetFilePath);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open tileset file!");
    }

    json tilesetData;
    file >> tilesetData;

    if (tilesetData.is_discarded()) {
        throw std::runtime_error("Error parsing tileset file");
    }

    parseTileset(tilesetData);
}

void LevelLoader::LoadCharacterSet(const std::string& filePath) {
    // Open and read the JSON file for characters
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open character file!");
    }

    json characterData;
    file >> characterData;
    if (characterData.is_discarded()) {
        throw std::runtime_error("Error parsing character JSON file");
    }

    // Parse each character from the JSON
    for (const auto& charData : characterData["characters"]) {
        CharacterDefinition charDef;
        charDef.id = charData["id"].get<int>();
        charDef.name = charData["name"].get<std::string>();
        charDef.type = charData["type"].get<std::string>();
        charDef.speed = charData["speed"].get<float>();

        characterDefinitions[charDef.id] = charDef;
    }
}
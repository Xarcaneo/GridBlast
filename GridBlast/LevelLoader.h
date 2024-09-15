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
    int collision; 
};

struct CharacterDefinition {
    int id;
    std::string name;
    std::string type;
    float speed;
};

struct Layer {
    std::string name;
    std::vector<std::vector<int>> data;
};

class LevelLoader {
public:
    LevelLoader() = default;

    void LoadLevel(const std::string& filePath);

    int getMapWidth() const { return mapWidth; }
    int getMapHeight() const { return mapHeight; }
    const std::unordered_map<int, TileDefinition>& getTileDefinitions() const { return tileDefinitions; }
    const std::unordered_map<int, CharacterDefinition>& getCharacterDefinitions() const { return characterDefinitions; }
    const std::vector<Layer>& getLayers() const { return layers; }

private:
    void LoadTileset(const std::string& tilesetFilePath);
    void LoadCharacterSet(const std::string& filePath); 

    int mapWidth;
    int mapHeight;
    std::unordered_map<int, TileDefinition> tileDefinitions;
    std::unordered_map<int, CharacterDefinition> characterDefinitions;
    std::vector<Layer> layers;

    void parseJSON(const nlohmann::json& jsonData);
    void parseTileset(const nlohmann::json& tilesetData);
};

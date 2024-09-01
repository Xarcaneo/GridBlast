#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <glm/glm.hpp>

class GameConfig {
public:
    // Initialize with a default tile size
    static void SetTileSize(const glm::vec2& size) { tileSize = size; }
    static glm::vec2 GetTileSize() { return tileSize; }
     
    static glm::mat4 projectionMatrix; // Projection matrix
private:
    static glm::vec2 tileSize; // Static variable to store tile size
};

#endif // GAME_CONFIG_H

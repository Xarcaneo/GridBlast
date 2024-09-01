#include "GameConfig.h"

// Initialize the static tile size with a default value (e.g., 32x32)
glm::vec2 GameConfig::tileSize = glm::vec2(32.0f, 32.0f);

// Define the static projectionMatrix
glm::mat4 GameConfig::projectionMatrix = glm::mat4(1.0f); // Initialize with an identity matrix
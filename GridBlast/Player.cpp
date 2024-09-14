#include "Player.h"
#include <iostream>
#include "ResourceManager.h"
#include "ServiceRegistry.h"
#include "ICameraService.h"

Player::Player(const Texture& texture, const glm::vec2& position, float speed)
    : Character(texture, position, speed) {
}

// Function to process input
void Player::ProcessInput(InputManager& inputManager) {
    // Movement directions
    glm::vec2 direction(0.0f, 0.0f);

    // Check for key holds and adjust direction accordingly
    if (inputManager.IsKeyHeld(GLFW_KEY_W)) {
        direction.y -= 1.0f;  // Move up
    }
    if (inputManager.IsKeyHeld(GLFW_KEY_S)) {
        direction.y += 1.0f;  // Move down
    }
    if (inputManager.IsKeyHeld(GLFW_KEY_A)) {
        direction.x -= 1.0f;  // Move left
    }
    if (inputManager.IsKeyHeld(GLFW_KEY_D)) {
        direction.x += 1.0f;  // Move right
    }

    // Normalize the direction vector to prevent faster diagonal movement
    if (direction.x != 0.0f || direction.y != 0.0f) {
        direction = glm::normalize(direction);
        Move(direction);  // Call the Move function on the current Player instance
    }

    // Get the player's position
    glm::vec2 playerPosition = GetPosition();

    // Update the camera's position and target to follow the player
    auto cameraService = ServiceRegistry::getInstance().getService<ICameraService>();
    cameraService->setPosition(glm::vec3(playerPosition, 5.0f));  // Camera stays 3 units above the player
    cameraService->setTarget(glm::vec3(playerPosition, 0.0f));    // Camera looks at the player
}
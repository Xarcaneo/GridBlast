// Player.cpp
#include "Player.h"
#include <iostream>
#include "ResourceManager.h"
#include "ServiceRegistry.h"
#include "ICameraService.h"
#include "IRenderService.h"

Player::Player(const Texture& texture, const glm::vec2& position, float speed)
    : Character(texture, position, speed) {
}

void Player::ProcessInput(InputManager& inputManager) {
    if (!isMoving) {
        // Get the tile size from the render service
        std::shared_ptr<IRenderService> retrievedRenderService = ServiceRegistry::getInstance().getService<IRenderService>();
        glm::vec2 tileSize = retrievedRenderService->getTileSize();

        glm::vec2 direction(0.0f, 0.0f);

        // Check for key presses and set the direction
        if (inputManager.IsKeyHeld(GLFW_KEY_W)) {
            direction.y -= 1.0f * tileSize.y;  // Move up
        }
        else if (inputManager.IsKeyHeld(GLFW_KEY_S)) {
            direction.y += 1.0f * tileSize.y;  // Move down
        }
        else if (inputManager.IsKeyHeld(GLFW_KEY_A)) {
            direction.x -= 1.0f * tileSize.x;  // Move left
        }
        else if (inputManager.IsKeyHeld(GLFW_KEY_D)) {
            direction.x += 1.0f * tileSize.x;  // Move right
        }

        // If a movement key was pressed
        if (direction.x != 0.0f || direction.y != 0.0f) {
            targetPosition = position + direction;
            isMoving = true;
            SetNextPosition(direction);
        }
    }
}

void Player::Update(float deltaTime) {
    
    Move(deltaTime);

    // Update the camera to follow the player
    glm::vec2 playerPosition = GetPosition();
    auto cameraService = ServiceRegistry::getInstance().getService<ICameraService>();
    cameraService->setPosition(glm::vec3(playerPosition, 5.0f));
    cameraService->setTarget(glm::vec3(playerPosition, 0.0f));
}

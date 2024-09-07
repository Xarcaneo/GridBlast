#include "Player.h"
#include <iostream>
#include "ResourceManager.h"

Player::Player(const Texture& texture, const glm::vec2& position, float speed)
    : Character(texture, position, speed) {
}

    // Function to process input
    void Player::ProcessInput(GLFWwindow* window) {
    // Movement directions
    glm::vec2 direction(0.0f, 0.0f);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        direction.y -= 1.0f;  // Move up
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        direction.y += 1.0f;  // Move down
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        direction.x -= 1.0f;  // Move left
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        direction.x += 1.0f;  // Move right
    }

    // Normalize the direction vector to prevent faster diagonal movement
    if (direction.x != 0.0f || direction.y != 0.0f) {
        direction = glm::normalize(direction);
        Move(direction);  // Call the Move function on the current Player instance
    }
}
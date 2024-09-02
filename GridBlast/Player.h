#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <GLFW/glfw3.h>

class Player : public Character {
public:
    Player(const Texture& texture, const glm::vec2& position, float speed);

    // Additional player-specific functions
    void ProcessInput(GLFWwindow* window);

    void Move(const glm::vec2& direction) override {
        // Add any additional player-specific movement logic here
        Character::Move(direction);  // Call the base class method
    }
};

#endif // PLAYER_H

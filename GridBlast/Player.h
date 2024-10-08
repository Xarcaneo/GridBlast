#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <GLFW/glfw3.h>
#include "InputManager.h"

class Player : public Character {
public:
    Player(const Texture& texture, const glm::vec2& position, float speed);

    // Additional player-specific functions
    void ProcessInput(InputManager& inputManager);

    void Move(float deltaTime) override {
        // Add any additional player-specific movement logic here
        Character::Move(deltaTime);  // Call the base class method
    }

    void Update(float deltaTime) override;
};

#endif // PLAYER_H

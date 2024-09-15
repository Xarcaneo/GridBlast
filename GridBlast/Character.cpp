#include "Character.h"
#include "ResourceManager.h"
#include "IRenderService.h"
#include "ServiceRegistry.h"
#include <iostream>

// Definition of the static SpriteRenderer
SpriteRenderer Character::spriteRenderer;
bool Character::isRendererInitialized = false;

Character::Character(const Texture& texture, const glm::vec2& position, float speed, float rotate, const glm::vec3& color)
    : texture(texture),
    position(position),
    nextPosition(glm::vec2(0,0)),
    targetPosition(position),
    speed(speed),
    rotate(rotate),
    color(color),
    isMoving(false) {
    // Initialize the renderer only once
    if (!isRendererInitialized) {
        spriteRenderer.Initialize();
        isRendererInitialized = true;
    }
}

void Character::SetPosition(const glm::vec2& position) {
    this->position = position;
}

glm::vec2 Character::GetPosition() const {
    return position;
}

// Set next position based on the direction
void Character::SetNextPosition(const glm::vec2& direction) {
    // Get the tile size from the render service
    std::shared_ptr<IRenderService> renderService = ServiceRegistry::getInstance().getService<IRenderService>();
    glm::vec2 tileSize = renderService->getTileSize();

    // Calculate the next position based on the current position and direction
    nextPosition = (position + direction) / tileSize;
}

// Get the next position
glm::vec2 Character::GetNextPosition() const {
    return nextPosition;
}

void Character::Render() const {
    std::shared_ptr<IRenderService> retrievedRenderService = ServiceRegistry::getInstance().getService<IRenderService>();
    glm::vec2 tileSize = retrievedRenderService->getTileSize();
    spriteRenderer.Render(texture, position, tileSize, rotate, color, 0, 0); // Rendering the character
}

void Character::Move(float deltaTime) {
    if (isMoving) {
        glm::vec2 direction = glm::normalize(targetPosition - position);
        glm::vec2 movement = direction * speed * deltaTime;

        // Check if the movement overshoots the target
        if (glm::length(movement) >= glm::length(targetPosition - position)) {
            position = targetPosition;
            isMoving = false;
        }
        else {
            position += movement;
        }
    }
}

void Character::StopMove()
{
    isMoving = false;
    nextPosition = glm::vec2(0,0);
}

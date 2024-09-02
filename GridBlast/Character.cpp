#include "Character.h"
#include "ResourceManager.h"
#include "IRenderService.h"
#include "ServiceRegistry.h"
#include <iostream>

// Definition of the static SpriteRenderer
SpriteRenderer Character::spriteRenderer;
bool Character::isRendererInitialized = false;

Character::Character(const Texture& texture, const glm::vec2& position, float speed, float rotate, const glm::vec3& color)
    :texture(texture), position(position), speed(speed), rotate(rotate), color(color) {
    // Initialize the renderer only once
    if (!isRendererInitialized) {
        spriteRenderer.Initialize();
        isRendererInitialized = true;
    }
}

void Character::Move(const glm::vec2& direction) {
    // Update position based on direction and speed
    position += direction * speed;
}

void Character::SetPosition(const glm::vec2& position) {
    this->position = position;
}

glm::vec2 Character::GetPosition() const {
    return position;
}

void Character::Render() const {
    std::shared_ptr<IRenderService> retrievedRenderService = ServiceRegistry::getInstance().getService<IRenderService>();
    glm::vec2 tileSize = retrievedRenderService->getTileSize();
    spriteRenderer.Render(texture, position, tileSize, rotate, color, 0, 0); // Rendering the character
}
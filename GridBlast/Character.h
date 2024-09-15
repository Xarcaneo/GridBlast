#ifndef CHARACTER_H
#define CHARACTER_H

#include <glm/glm.hpp>
#include "SpriteRenderer.h"

class Character {
public:
    Character(const Texture& texture, const glm::vec2& position, float speed, float rotate = 0.0f, const glm::vec3& color = glm::vec3(1.0f));
    virtual ~Character() = default;
    virtual void SetPosition(const glm::vec2& position);
    virtual void Render() const; // Concrete render method
    virtual void Update(float deltaTime) = 0;

    void StopMove();

    glm::vec2 GetPosition() const;
    // Setter for next grid position based on direction
    void SetNextPosition(const glm::vec2& direction);
    // Getter for the next position
    glm::vec2 GetNextPosition() const;

protected:
    virtual void Move(float deltaTime);

    const Texture& texture;
    glm::vec2 position;  // Position of the character in the game world
    glm::vec2 nextPosition; // Next grid position after movement
    float speed;         // Movement speed of the character

    glm::vec2 targetPosition;
    bool isMoving;

    float rotate;
    glm::vec3 color;

    static SpriteRenderer spriteRenderer; // Static renderer shared by all Character instances
    static bool isRendererInitialized;  // Static flag to ensure initialization only once
};

#endif // CHARACTER_H

#ifndef CHARACTER_H
#define CHARACTER_H

#include <glm/glm.hpp>
#include "SpriteRenderer.h"
#include "ResourceManager.h"

class Character {
public:
    Character(const Texture& texture, const glm::vec2& position, float speed, float rotate = 0.0f, const glm::vec3& color = glm::vec3(1.0f));
    virtual ~Character() = default;

    // Movement functions
    virtual void Move(const glm::vec2& direction);
    virtual void SetPosition(const glm::vec2& position);
    virtual void Render() const; // Concrete render method
    glm::vec2 GetPosition() const;

protected:
    const Texture& texture;
    glm::vec2 position;  // Position of the character in the game world
    float speed;         // Movement speed of the character

    float rotate;
    glm::vec3 color;

    static SpriteRenderer spriteRenderer; // Static renderer shared by all Character instances
    static bool isRendererInitialized;  // Static flag to ensure initialization only once
};

#endif // CHARACTER_H

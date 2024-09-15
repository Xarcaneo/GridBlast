#ifndef TILE_H
#define TILE_H

#include "SpriteRenderer.h"

class Tile {
public:
    Tile(const Texture& texture, const glm::vec2& position, int row, int column, bool collision = false,
         float rotate = 0.0f, const glm::vec3& color = glm::vec3(1.0f));

    virtual ~Tile() = default; // Virtual destructor

    virtual void Render() const; // Concrete render method

    glm::vec2 GetPosition() const;  // Method to get the position of the tile
    bool IsCollidable() const;      // Getter for collision property

protected:
    const Texture& texture;
    glm::vec2 position;
    int row;
    int column;
    float rotate;
    glm::vec3 color;
    bool collision; 

    static SpriteRenderer spriteRenderer; // Static renderer shared by all Tile instances
    static bool isRendererInitialized;  // Static flag to ensure initialization only once
};

#endif // TILE_H

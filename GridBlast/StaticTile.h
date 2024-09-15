#ifndef STATIC_TILE_H
#define STATIC_TILE_H

#include "Tile.h"

class StaticTile : public Tile {
public:
    StaticTile(const Texture& texture, const glm::vec2& position, int row, int column, bool collision, 
        float rotate = 0.0f, const glm::vec3& color = glm::vec3(1.0f))
        : Tile(texture, position, row, column, collision, rotate, color) {}

    // No need to override Render unless static tiles have special rendering logic
};

#endif // STATIC_TILE_H

#pragma once
#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "Texture.h"
#include <glm/glm.hpp>

class SpriteRenderer {
public:
    SpriteRenderer();
    ~SpriteRenderer();

    bool Initialize(); // Initialize shaders, buffers, etc.
    void Render(const Texture& texture, const glm::vec2& position, const glm::vec2& size = glm::vec2(16, 16),
        float rotate = 0.0f, const glm::vec3& color = glm::vec3(1.0f),
        int row = 0, int column = 0); // Render the sprite with row and column for tile

private:
    unsigned int VAO, VBO, EBO; // Vertex Array Object, Vertex Buffer Object, Element Buffer Object
    unsigned int shaderProgram; // Shader program ID

    bool compileShaders(); // Compile and link shaders
    unsigned int compileShader(unsigned int type, const std::string& source); // Helper function to compile a shader
};

#endif // SPRITE_RENDERER_H

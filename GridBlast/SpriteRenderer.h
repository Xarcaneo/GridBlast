#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glm/glm.hpp>
#include <memory>
#include "Shader.h"
#include "Texture.h"

class SpriteRenderer {
public:
    SpriteRenderer();
    ~SpriteRenderer();

    bool Initialize();
    void Render(const Texture& texture, const glm::vec2& position, const glm::vec2& size,
        float rotate, const glm::vec3& color, int row, int column);

private:
    GLuint VAO, VBO, EBO;
    std::shared_ptr<Shader> shaderProgram;  // Shader program loaded from ResourceManager
};

#endif // SPRITE_RENDERER_H

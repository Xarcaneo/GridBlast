#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <map>
#include <string>
#include <glm/glm.hpp>
#include <memory>
#include "Shader.h"
#include "Font.h"

class TextRenderer {
public:
    TextRenderer();
    ~TextRenderer();

    // Load a font
    void Load(const std::shared_ptr<Font>& font);

    // Render text on the screen
    void RenderText(const std::string& text, float x, float y, float scale, const glm::vec3& color);

    // Get the size of the rendered text
    glm::vec2 GetTextSize(const std::string& text) const;

private:
    std::map<char, Glyph> Glyphs;  // Map to store the Glyphs
    GLuint VAO, VBO;               // Vertex Array Object and Vertex Buffer Object for text rendering
    std::shared_ptr<Shader> shaderProgram;  // Shader program loaded from ResourceManager

    void setupRenderData();               // Setup VAO/VBO for text rendering
};

#endif // TEXT_RENDERER_H

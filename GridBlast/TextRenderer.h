#pragma once
#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <map>
#include <string>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "IRenderService.h"
#include "ServiceRegistry.h"
#include "Font.h"

class TextRenderer {
public:
    TextRenderer();
    ~TextRenderer();

    // Load a font
    void Load(const std::shared_ptr<Font>& font);

    // Render text on the screen
    void RenderText(const std::string& text, float x, float y, float scale, const glm::vec3& color);

private:
    std::map<char, Glyph> Glyphs;  // Map to store the Glyphs
    unsigned int VAO, VBO;                // Vertex Array Object and Vertex Buffer Object for text rendering
    unsigned int shaderProgram;           // Shader program ID

    void setupRenderData();               // Setup VAO/VBO for text rendering
    bool compileShaders();                // Compile shaders
    unsigned int compileShader(unsigned int type, const std::string& source); // Compile individual shader
};

#endif

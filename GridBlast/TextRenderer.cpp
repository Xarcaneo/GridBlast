#include "TextRenderer.h"
#include "ServiceRegistry.h"
#include "IResourceService.h"
#include "IRenderService.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

TextRenderer::TextRenderer()
    : VAO(0), VBO(0), shaderProgram(nullptr) {
    setupRenderData();

    // Retrieve the shader program from ResourceManager
    shaderProgram = ServiceRegistry::getInstance().getService<IResourceService>()->GetShader("textShader");

    if (!shaderProgram) {
        std::cerr << "Failed to load shader program: textShader" << std::endl;
    }
}

TextRenderer::~TextRenderer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void TextRenderer::Load(const std::shared_ptr<Font>& font) {
    if (font) {
        // Update TextRenderer's Glyphs with the loaded font's Glyphs
        this->Glyphs = font->GetGlyphs();
    }
    else {
        std::cerr << "ERROR::TEXTRENDERER::LOADFONT: Failed to load font" << std::endl;
    }
}

void TextRenderer::RenderText(const std::string& text, float x, float y, float scale, const glm::vec3& color) {
    // Activate blending for text rendering
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Use the shader program for text rendering
    shaderProgram->Use();

    // Retrieve the projection matrix from IRenderService
    std::shared_ptr<IRenderService> retrievedRenderService = ServiceRegistry::getInstance().getService<IRenderService>();
    glm::mat4 projection = retrievedRenderService->getProjectionMatrix();

    // Set the projection matrix in the shader
    shaderProgram->SetMatrix4("projection", projection);

    // Set the text color
    shaderProgram->SetVector3f("textColor", color);

    // Render each character in the text string
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        Glyph glyph = Glyphs[*c];

        float xpos = x + glyph.Bearing.x * scale;
        float ypos = y - (glyph.Size.y - glyph.Bearing.y) * scale;

        float w = glyph.Size.x * scale;
        float h = glyph.Size.y * scale;

        // Update VBO for each character's quad
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };

        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, glyph.TextureID);

        // Update the VBO content
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Advance to the next character
        x += (glyph.Advance >> 6) * scale;
    }

    // Unbind after rendering
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Disable blending to avoid affecting other rendering parts
    glDisable(GL_BLEND);
}

void TextRenderer::setupRenderData() {
    // Configure VAO/VBO for texture quads
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    // Set attribute pointers
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

glm::vec2 TextRenderer::GetTextSize(const std::string& text) const {
    float width = 0.0f;
    float height = 0.0f;

    // Iterate through each character in the string
    for (std::string::const_iterator c = text.begin(); c != text.end(); c++) {
        Glyph glyph = Glyphs.at(*c);

        // Increase the total width by the advance of the glyph
        width += (glyph.Advance >> 6);  // Advance is in 1/64th pixels, so bit shift by 6
        // Track the maximum height of any character in the string
        height = std::max(height, static_cast<float>(glyph.Size.y));
    }

    // Return the width and height as a 2D vector (width, height)
    return glm::vec2(width, height);
}

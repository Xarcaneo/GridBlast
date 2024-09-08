#include "TextRenderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <GL/glew.h>

// Vertex and Fragment shader source code
const char* textVertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>

out vec2 TexCoords;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
    // Flip the Y-coordinate here
    TexCoords = vec2(vertex.z, 1.0 - vertex.w);
}
)";

const char* textFragmentShaderSource = R"(
#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    color = vec4(textColor, 1.0) * sampled;
}
)";

TextRenderer::TextRenderer()
    : VAO(0), VBO(0), shaderProgram(0) {
    setupRenderData();
    compileShaders();
}

TextRenderer::~TextRenderer() {
    // Clean up OpenGL resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
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
    glUseProgram(shaderProgram);

    // Retrieve the projection matrix from IRenderService
    std::shared_ptr<IRenderService> retrievedRenderService = ServiceRegistry::getInstance().getService<IRenderService>();
    glm::mat4 projection = retrievedRenderService->getProjectionMatrix();

    // Set the projection matrix in the shader
    unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Set the text color
    glUniform3f(glGetUniformLocation(shaderProgram, "textColor"), color.x, color.y, color.z);

    // Render each character in the text string
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        Glyph glyph = Glyphs[*c];

        float xpos = x + glyph.Bearing.x;  // Remove scaling on bearing
        float ypos = y - (glyph.Size.y - glyph.Bearing.y);  // Remove scaling on size

        float w = glyph.Size.x;  // Remove scaling from width
        float h = glyph.Size.y;  // Remove scaling from height

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

        // Advance to the next character (>> 6 is a bitwise operation to divide by 64)
        x += (glyph.Advance >> 6);
    }

    // Unbind after rendering
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Disable blending to avoid affecting other rendering parts
    glDisable(GL_BLEND);
}

bool TextRenderer::compileShaders() {
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, textVertexShaderSource);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, textFragmentShaderSource);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return false;
    }

    // Clean up shaders as they are linked into the program now
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

unsigned int TextRenderer::compileShader(unsigned int type, const std::string& source) {
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    // Check for compilation errors
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
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

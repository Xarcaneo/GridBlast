#include "SpriteRenderer.h"
#include "IRenderService.h"
#include "ServiceRegistry.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

// Vertex and Fragment shader source code
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    gl_Position = projection * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D image;
uniform vec3 spriteColor;

void main()
{
    FragColor = texture(image, TexCoord) * vec4(spriteColor, 1.0);
}
)";

SpriteRenderer::SpriteRenderer()
    : VAO(0), VBO(0), EBO(0), shaderProgram(0) {
}

SpriteRenderer::~SpriteRenderer() {
    // Clean up OpenGL resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
}

bool SpriteRenderer::Initialize() {
    // Initialize vertex data for a quad
    float vertices[] = {
        // positions          // texture coords
         1.0f,  1.0f, 0.0f,   1.0f, 1.0f, // top right
         1.0f, -1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, // bottom left
        -1.0f,  1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };

    unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    // Generate and bind the Vertex Array Object
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Bind and set vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind and set element buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Define vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind the VAO
    glBindVertexArray(0);

    // Compile and link shaders
    return compileShaders();
}

void SpriteRenderer::Render(const Texture& texture, const glm::vec2& position, const glm::vec2& size,
    float rotate, const glm::vec3& color, int row, int column) {
    // Use the shader program
    glUseProgram(shaderProgram);

    // Get the texture dimensions
    int textureWidth, textureHeight;
    glBindTexture(GL_TEXTURE_2D, texture.GetTextureID());
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textureWidth);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &textureHeight);

    // Calculate texture coordinates based on row, column, and texture dimensions
    float tileWidth = size.x / textureWidth;  // Tile width in texture coordinates
    float tileHeight = size.y / textureHeight; // Tile height in texture coordinates

    glm::vec2 texCoordsMin(column * tileWidth, 1.0f - (row + 1) * tileHeight);
    glm::vec2 texCoordsMax((column + 1) * tileWidth, 1.0f - row * tileHeight);

    // Create transformation matrix for the sprite
    glm::mat4 model = glm::mat4(1.0f);  // Identity matrix
    model = glm::translate(model, glm::vec3(position, 0.0f));  // Translate to the position
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate
    model = glm::scale(model, glm::vec3(size, 1.0f)); // Scale to the correct size

    // Get the projection matrix from GameConfig
    std::shared_ptr<IRenderService> retrievedRenderService = ServiceRegistry::getInstance().getService<IRenderService>();
    glm::mat4 projection = retrievedRenderService->getProjectionMatrix();

    // Send matrices to the shader
    unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
    unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Set the sprite color
    glUniform3f(glGetUniformLocation(shaderProgram, "spriteColor"), color.x, color.y, color.z);

    // Bind the texture
    texture.Bind();

    // Update the vertex data with new texture coordinates
    float vertices[] = {
        // positions        // texture coords
        0.0f,  1.0f, 0.0f,  texCoordsMin.x, texCoordsMin.y, // top-left
        1.0f,  1.0f, 0.0f,  texCoordsMax.x, texCoordsMin.y, // top-right
        1.0f,  0.0f, 0.0f,  texCoordsMax.x, texCoordsMax.y, // bottom-right
        0.0f,  0.0f, 0.0f,  texCoordsMin.x, texCoordsMax.y  // bottom-left
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    // Bind the VAO and draw the quad
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

bool SpriteRenderer::compileShaders() {
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

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

unsigned int SpriteRenderer::compileShader(unsigned int type, const std::string& source) {
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

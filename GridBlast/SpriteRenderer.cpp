#include "SpriteRenderer.h"
#include "ServiceRegistry.h"
#include "IResourceService.h"
#include "IRenderService.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

SpriteRenderer::SpriteRenderer()
    : VAO(0), VBO(0), EBO(0), shaderProgram(nullptr) {
}

SpriteRenderer::~SpriteRenderer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
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

    // Retrieve the shader program from ResourceManager
    shaderProgram = ServiceRegistry::getInstance().getService<IResourceService>()->GetShader("spriteShader");

    if (!shaderProgram) {
        std::cerr << "Failed to load shader program: spriteShader" << std::endl;
        return false;
    }

    return true;
}

void SpriteRenderer::Render(const Texture& texture, const glm::vec2& position, const glm::vec2& size,
    float rotate, const glm::vec3& color, int row, int column) {

    // Use the shader program
    shaderProgram->Use();

    // Get the texture dimensions
    int textureWidth, textureHeight;
    glBindTexture(GL_TEXTURE_2D, texture.GetTextureID());
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textureWidth);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &textureHeight);

    // Calculate texture coordinates based on row, column, and texture dimensions
    float tileWidth = 1.0f / (textureWidth / size.x);  // Tile width in normalized texture coordinates
    float tileHeight = 1.0f / (textureHeight / size.y); // Tile height in normalized texture coordinates

    glm::vec2 texCoordsMin(column * tileWidth, 1.0f - (row + 1) * tileHeight);
    glm::vec2 texCoordsMax((column + 1) * tileWidth, 1.0f - row * tileHeight);

    // Create transformation matrix for the sprite (model matrix)
    glm::mat4 model = glm::mat4(1.0f);  // Identity matrix
    model = glm::translate(model, glm::vec3(position, 0.0f));  // Translate to the position
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate
    model = glm::scale(model, glm::vec3(size, 1.0f)); // Scale to the correct size

    // Get the view and projection matrices from RenderService
    auto retrievedRenderService = ServiceRegistry::getInstance().getService<IRenderService>();
    glm::mat4 view = retrievedRenderService->getViewMatrix();            // Get view matrix
    glm::mat4 projection = retrievedRenderService->getProjectionMatrix(); // Get projection matrix

    // Send matrices to the shader
    shaderProgram->SetMatrix4("model", model);
    shaderProgram->SetMatrix4("view", view);         // Set the view matrix
    shaderProgram->SetMatrix4("projection", projection); // Set the projection matrix
    shaderProgram->SetVector3f("spriteColor", color);

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



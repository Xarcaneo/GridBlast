#include "Texture.h"
#include <stb/stb_image.h>
#include <iostream>

Texture::Texture(const std::string& id, const std::string& filePath)
    : Resource(id), filePath(filePath), textureID(0) {}

Texture::~Texture() {
    Unload();
}

bool Texture::Load() {
    // Load the texture using stb_image or any other image loading library
    int width, height, channels;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Failed to load texture: " << filePath << std::endl;
        return false;
    }

    // Generate and bind a new OpenGL texture
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters (wrap, filter, etc.)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload the texture data to the GPU
    GLenum format = channels == 4 ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Free the image data and unbind the texture
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}

void Texture::Bind() const {
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::Unload() {
    if (textureID) {
        glDeleteTextures(1, &textureID);
        textureID = 0;
    }
}

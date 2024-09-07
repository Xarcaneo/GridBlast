#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include "Resource.h"
#include <GL/glew.h>
#include <string>

class Texture : public Resource {
public:
    Texture(const std::string& id, const std::string& filePath);
    ~Texture();

    bool Load() override;  // Override the Load method to load textures
    void Bind() const;     // Bind the texture for use
    GLuint GetTextureID() const; // Getter for textureID    

private:
    std::string filePath;  // Path to the texture file
    GLuint textureID;      // OpenGL texture ID

    void Unload();         // Cleanup the texture resource
};

#endif // TEXTURE_H

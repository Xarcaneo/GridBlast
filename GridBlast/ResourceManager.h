#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>
#include <memory>
#include "Texture.h"

class ResourceManager {
public:
    ResourceManager() = default;
    ~ResourceManager() = default;

    // Load a texture and store it in the resource map
    std::shared_ptr<Texture> LoadTexture(const std::string& id, const std::string& filePath);

    // Get a texture by its ID
    std::shared_ptr<Texture> GetTexture(const std::string& id) const;

    // Unload a texture by its ID
    void UnloadTexture(const std::string& id);

    // Unload all textures
    void UnloadAllTextures();

private:
    std::map<std::string, std::shared_ptr<Resource>> resources;
};

#endif // RESOURCE_MANAGER_H

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>
#include <memory>
#include "IResourceService.h"
#include "Font.h"

class ResourceManager : public IResourceService {
public:
    ResourceManager() = default;
    ~ResourceManager() override = default;

    // Load a texture and store it in the resource map
    std::shared_ptr<Texture> LoadTexture(const std::string& id, const std::string& filePath) override;
    // Get a texture by its ID
    std::shared_ptr<Texture> GetTexture(const std::string& id) const override;
    // Unload a texture by its ID
    void UnloadTexture(const std::string& id) override;
    // Unload all textures
    void UnloadAllTextures() override;

    std::shared_ptr<Font> LoadFont(const std::string& id, const std::string& fontPath);
    std::shared_ptr<Font> GetFont(const std::string& id) const;
    void UnloadFont(const std::string& id);
    void UnloadAllFonts();

private:
    std::map<std::string, std::shared_ptr<Texture>> resources; // Manage textures by ID
    std::map<std::string, std::shared_ptr<Font>> fonts;
};

#endif // RESOURCE_MANAGER_H

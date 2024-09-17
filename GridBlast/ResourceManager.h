#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>
#include <memory>
#include "IResourceService.h"
#include "Font.h"
#include "Shader.h"  // Include Shader here

class ResourceManager : public IResourceService {
public:
    ResourceManager() = default;
    ~ResourceManager() override = default;

    // Textures
    std::shared_ptr<Texture> LoadTexture(const std::string& id, const std::string& filePath) override;
    std::shared_ptr<Texture> GetTexture(const std::string& id) const override;
    void UnloadTexture(const std::string& id) override;
    void UnloadAllTextures() override;

    // Fonts
    std::shared_ptr<Font> LoadFont(const std::string& id, const std::string& fontPath);
    std::shared_ptr<Font> GetFont(const std::string& id) const;
    void UnloadFont(const std::string& id);
    void UnloadAllFonts();

    // Shaders
    std::shared_ptr<Shader> LoadShader(const std::string& id, const std::string& vertexPath, const std::string& fragmentPath) override;
    std::shared_ptr<Shader> GetShader(const std::string& id) const override;
    void UnloadShader(const std::string& id) override;
    void UnloadAllShaders() override;

    void LoadResourcesFromJSON(const std::string& filePath) override;
private:
    std::map<std::string, std::shared_ptr<Texture>> resources; // Manage textures by ID
    std::map<std::string, std::shared_ptr<Font>> fonts;
    std::map<std::string, std::shared_ptr<Shader>> shaders; // Manage shaders by ID
};

#endif // RESOURCE_MANAGER_H

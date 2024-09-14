#pragma once

#include <string>
#include <memory>
#include "Texture.h"
#include "Font.h"
#include "Shader.h"  // Include Shader here
#include "IGameService.h"

class IResourceService : public IGameService {
public:
    virtual ~IResourceService() override = default;

    // Virtual methods for managing textures
    virtual std::shared_ptr<Texture> LoadTexture(const std::string& id, const std::string& filePath) = 0;
    virtual std::shared_ptr<Texture> GetTexture(const std::string& id) const = 0;
    virtual void UnloadTexture(const std::string& id) = 0;
    virtual void UnloadAllTextures() = 0;

    // Virtual methods for managing fonts
    virtual std::shared_ptr<Font> LoadFont(const std::string& id, const std::string& fontPath) = 0;
    virtual std::shared_ptr<Font> GetFont(const std::string& id) const = 0;
    virtual void UnloadFont(const std::string& id) = 0;
    virtual void UnloadAllFonts() = 0;

    // Virtual methods for managing shaders
    virtual std::shared_ptr<Shader> LoadShader(const std::string& id, const std::string& vertexPath, const std::string& fragmentPath) = 0;
    virtual std::shared_ptr<Shader> GetShader(const std::string& id) const = 0;
    virtual void UnloadShader(const std::string& id) = 0;
    virtual void UnloadAllShaders() = 0;
};

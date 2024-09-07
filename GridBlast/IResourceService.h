#pragma once
#include <string>
#include <memory>
#include "Texture.h"
#include "IGameService.h"

class IResourceService : public IGameService {
public:
    virtual ~IResourceService() override = default;

    // Virtual methods for managing textures
    virtual std::shared_ptr<Texture> LoadTexture(const std::string& id, const std::string& filePath) = 0;
    virtual std::shared_ptr<Texture> GetTexture(const std::string& id) const = 0;
    virtual void UnloadTexture(const std::string& id) = 0;
    virtual void UnloadAllTextures() = 0;
};

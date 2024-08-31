#include "ResourceManager.h"

std::shared_ptr<Texture> ResourceManager::LoadTexture(const std::string& id, const std::string& filePath) {
    auto it = resources.find(id);
    if (it != resources.end()) {
        return std::dynamic_pointer_cast<Texture>(it->second);
    }

    auto texture = std::make_shared<Texture>(id, filePath);
    if (texture->Load()) {
        resources[id] = texture;
        return texture;
    }

    return nullptr;
}

std::shared_ptr<Texture> ResourceManager::GetTexture(const std::string& id) const {
    auto it = resources.find(id);
    if (it != resources.end()) {
        return std::dynamic_pointer_cast<Texture>(it->second);
    }
    return nullptr;
}

void ResourceManager::UnloadTexture(const std::string& id) {
    auto it = resources.find(id);
    if (it != resources.end()) {
        resources.erase(it);
    }
}

void ResourceManager::UnloadAllTextures() {
    resources.clear();
}

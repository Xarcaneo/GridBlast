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

std::shared_ptr<Font> ResourceManager::LoadFont(const std::string& id, const std::string& fontPath) {
    auto it = fonts.find(id);
    if (it != fonts.end()) {
        return it->second;
    }

    auto font = std::make_shared<Font>(id, fontPath);
    if (font->Load()) {
        fonts[id] = font;
        return font;
    }

    return nullptr;
}

std::shared_ptr<Font> ResourceManager::GetFont(const std::string& id) const {
    auto it = fonts.find(id);
    if (it != fonts.end()) {
        return it->second;
    }
    return nullptr;
}

void ResourceManager::UnloadFont(const std::string& id) {
    auto it = fonts.find(id);
    if (it != fonts.end()) {
        fonts.erase(it);
    }
}

void ResourceManager::UnloadAllFonts() {
    fonts.clear();
}

std::shared_ptr<Shader> ResourceManager::LoadShader(const std::string& id, const std::string& vertexPath, const std::string& fragmentPath) {
    auto it = shaders.find(id);
    if (it != shaders.end()) {
        return it->second;
    }

    auto shader = std::make_shared<Shader>(id, vertexPath, fragmentPath);
    if (shader->Load()) {
        shaders[id] = shader;
        return shader;
    }

    return nullptr;
}

std::shared_ptr<Shader> ResourceManager::GetShader(const std::string& id) const {
    auto it = shaders.find(id);
    if (it != shaders.end()) {
        return it->second;
    }
    return nullptr;
}

void ResourceManager::UnloadShader(const std::string& id) {
    auto it = shaders.find(id);
    if (it != shaders.end()) {
        shaders.erase(it);
    }
}

void ResourceManager::UnloadAllShaders() {
    shaders.clear();
}
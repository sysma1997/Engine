#include "ResourceManager.h"

std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Texture> ResourceManager::textures;

ResourceManager::ResourceManager() {}
ResourceManager::~ResourceManager() {}

Shader ResourceManager::LoadShader(std::string name, const char* vertexPath, const char* fragmentPath) {
    shaders[name] = Shader(vertexPath, fragmentPath);
    return shaders[name];
}
Shader ResourceManager::GetShader(std::string name) {
    return shaders[name];
}

Texture ResourceManager::LoadTexture(std::string name, const char* texturePath, bool alpha) {
    textures[name] = Texture(texturePath, alpha);
    return textures[name];
}
Texture ResourceManager::GetTexture(std::string name) {
    return textures[name];
}

void ResourceManager::Clear() {
    for (auto shader : shaders)
        glDeleteProgram(shader.second.id);
    for (auto texture : textures)
    {
        GLuint id{ texture.second.id };
        glDeleteTextures(1, &id);
    }
}
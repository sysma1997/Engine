#pragma once

#include <string>
#include <map>

#include "Shader.h"
#include "Texture.h"

class ResourceManager {
private:
    static std::map<std::string, Shader> shaders;
    static std::map<std::string, Texture> textures;

public:
    ResourceManager();
    ~ResourceManager();

    static Shader LoadShader(std::string name, const char* vertexPath, const char* framePath);
    static Shader GetShader(std::string name);

    static Texture LoadTexture(std::string name, const char* texturePath, bool rgba = false);
    static Texture GetTexture(std::string name);

    static void Clear();
};
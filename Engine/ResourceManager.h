#pragma once

#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <GL/glew.h>

#include "Shader.h"
#include "Texture.h"

class ResourceManager 
{
private:
	static std::map<std::string, Shader> shaders;
	static std::map<std::string, Texture> textures;

public:
	ResourceManager();
	~ResourceManager();

	static Shader LoadShader(std::string name, std::string vertexPath, std::string fragmentPath);
	static Shader GetShader(std::string name);
	static Texture LoadTexture(std::string name, std::string path, bool rgba = false);
	static Texture GetTexture(std::string name);
	static void Clear();
};
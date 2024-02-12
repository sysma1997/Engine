#include "ResourceManager.h"

std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Texture> ResourceManager::textures;

ResourceManager::ResourceManager() {}
ResourceManager::~ResourceManager() {}

Shader ResourceManager::LoadShader(std::string name, std::string vertexPath, std::string fragmentPath) {
	//shaders.insert(std::pair<std::string, Shader>(name, Shader{ vertexPath, fragmentPath }));
	shaders[name] = Shader{ vertexPath, fragmentPath };
	return shaders[name];
}
Shader ResourceManager::GetShader(std::string name) {
	return shaders[name];
}
Texture ResourceManager::LoadTexture(std::string name, std::string path, bool rgba) {
	//textures.insert(std::pair<std::string, Texture>(name, Texture{ path, rgba }));
	textures[name] = Texture{ path, rgba };
	return textures[name];
}
Texture ResourceManager::GetTexture(std::string name) {
	return textures[name];
}
void ResourceManager::Clear() {
	for (auto shader : shaders)
		glDeleteShader(shader.second.id);
	for (auto texture : textures) 
		glDeleteTextures(1, &texture.second.id);
}
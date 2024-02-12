#pragma once

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Texture
{
private:
	std::string LOG{ "SYSMA::ENGINE::TEXTURE::" };
public:
	GLuint id;
	unsigned int width;
	unsigned int height;

	Texture();
	Texture(std::string path, bool rgba = false);
	~Texture();

	void generate(unsigned int width, unsigned int height, std::string data);
	void bind() const;

	static void Init();
};
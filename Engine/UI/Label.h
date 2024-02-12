#pragma once

#include <iostream>
#include <string>
#include <map>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Shader.h"
#include "../Texture.h"
#include "../ResourceManager.h"

namespace UI {
	struct Character {
		unsigned int id;
		glm::ivec2 size;
		glm::ivec2 bearing;
		unsigned int advance;
	};

	class Label {
	private:
		std::string LOG{ "SYSMA::ENGINE::UI::LABEL::" };

		unsigned int VAO, VBO;
	public:
		std::map<char, Character> characters;
		Shader shader;

		Label(unsigned int width, unsigned int height);

		void load(std::string fontPath, unsigned int fontSizes);
		void render(std::string text, float x, float y, float scale = 1.0f, glm::vec3 color = glm::vec3{ 1.0f });
	};
}
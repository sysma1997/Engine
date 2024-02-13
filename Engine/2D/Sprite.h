#pragma once

#include <functional>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../Shader.h"
#include "../Texture.h"

namespace E2D {
	class Sprite {
	private:
		GLuint VAO;
		Shader shader;
		Texture texture;
		
	public:
		glm::vec2 position, size, velocity;
		float rotate;
		glm::vec3 color;

		Sprite(Shader& shader, Texture& texture);
		~Sprite();

		void draw();
	};
}
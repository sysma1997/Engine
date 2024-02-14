#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Shader.h"

namespace E2D {
	class Object {
	protected:
		GLuint VAO;
		Shader shader;

		float width, height;

	public:
		glm::vec2 position, size;
		float rotate;
		glm::vec3 color;

		Object(Shader& shader, float width, float height, bool isVertexInput = true);
		~Object();

		void updateWindowSize(float width, float height);

		virtual void draw() = 0;
	};
}
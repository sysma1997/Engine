#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Engine.h"
#include "../Shader.h"

namespace E2D {
	class Object {
	protected:
		GLuint VAO;
		Shader shader;

	public:
		glm::vec2 position, size;
		float rotate;
		glm::vec3 color;

		Object(Shader shader, bool isVertexInput = true);
		~Object();

		static bool CheckCollision(Object& objec1, Object& object2);

		void updateWindowSize();

		virtual void draw() = 0;
	};
}
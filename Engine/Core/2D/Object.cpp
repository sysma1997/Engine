#include "../../Include/2D/Object.h"

namespace E2D {
	Object::Object(Shader& shader, float width, float height, bool isVertexInput) :
		shader{ shader },
		width{ width }, height{ height }, 
		position{ 1.0f }, size{ 1.0f },
		rotate{ 0.0f },
		color{ 1.0f } {
		if (!isVertexInput) return;

		float vertices[]{
			// pos
			0.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f
		};

		GLuint VBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindVertexArray(VAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		updateWindowSize(width, height);
	}
	Object::~Object() {
		glDeleteVertexArrays(1, &VAO);
	}

	void Object::updateWindowSize(float width, float height) {
		glm::mat4 projection{ glm::ortho(0.0f, width, height, 0.0f) };
		shader.setMat4("projection", projection, true);
	}
}
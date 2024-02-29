#include "../../Include/2D/Object.h"

namespace E2D {
	Object::Object(Shader shader, bool isVertexInput) : 
		VAO{ 0 }, 
		shader{ shader }, 
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

		updateWindowSize();
	}
	Object::~Object() {
		glDeleteVertexArrays(1, &VAO);
	}

	bool Object::CheckCollision(Object& object1, Object& object2) {
		glm::vec2 object1StartCollision{ object1.position - (object1.size / 2.0f) };
		glm::vec2 object1EndCollision{ object1.position + (object1.size / 2.0f) };
		glm::vec2 object2StartCollision{ object2.position - (object2.size / 2.0f) };
		glm::vec2 object2EndCollision{ object2.position + (object2.size / 2.0f)};

		glm::vec2 differenceStart{ object1StartCollision - object2StartCollision };
		glm::vec2 differenceEnd{ object1EndCollision - object2EndCollision };

		if (differenceStart.x < object2.size.x && differenceStart.y < object2.size.y &&
			differenceEnd.x > -object2.size.x && differenceEnd.y > -object2.size.y)
			return true;

		return false;
	}

	void Object::updateWindowSize() {
		glm::mat4 projection{ glm::ortho(0.0f, Engine::FWidth, Engine::FHeight, 0.0f) };
		shader.setMat4("projection", projection, true);
	}
}
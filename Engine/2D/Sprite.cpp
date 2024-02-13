#include "Sprite.h"

namespace E2D {
	Sprite::Sprite(Shader& shader, Texture& texture) : 
		shader{ shader }, texture{ texture }, 
		position{ 1.0f }, size{ 10.0f }, velocity{ 60.0f }, 
		rotate{ 0.0f }, 
		color{ 1.0f } {
		float vertices[]{
			// pos      // tex
			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,

			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f
		};
		
		GLuint VBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindVertexArray(VAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	Sprite::~Sprite() {
		glDeleteVertexArrays(1, &VAO);
	}

	void Sprite::draw() {
		glm::mat4 model{ 1.0f };
		model = glm::translate(model, glm::vec3{ position, 0.0f });
		model = glm::translate(model, glm::vec3{ size * -0.5f, 0.0f });
		model = glm::rotate(model, glm::radians(rotate), glm::vec3{ 0.0f, 0.0f, 1.0f });
		model = glm::scale(model, glm::vec3{ size, 1.0f });
		
		shader.use();
		shader.setMat4("model", model);
		shader.setVec3("spriteColor", color);
		texture.bind();

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}
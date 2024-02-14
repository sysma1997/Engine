#include "../../Include/2D/Sprite.h"

namespace E2D {
	Sprite::Sprite(Texture& texture, float width, float height) : 
		Object{ *(new Shader{"Shaders/2D/Sprite.vert", "Shaders/2D/Sprite.frag"}), width, height, false},
		texture{ texture } {
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

		glm::mat4 projection{ glm::ortho(0.0f, width, height, 0.0f) };
		shader.setMat4("projection", projection, true);
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
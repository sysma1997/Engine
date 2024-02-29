#include "../../Include/2D/SpriteAnimated.h"

namespace E2D {
	SpriteAnimated::SpriteAnimated(std::vector<Texture> textures) :
		Object{ Shader{ "Shaders/2D/Sprite.vert", "Shaders/2D/Sprite.frag" }, false },
		textures{ textures }, indexTexture{ 0 }, currentTime{ 0.0f }, timeChangeTexture{ 0.2f } {
		float vertices[]{
			// pos      //tex
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
		glBindVertexArray(0);

		updateWindowSize();
	}

	void SpriteAnimated::draw() {
		currentTime += Engine::DeltaTime;
		if (currentTime > timeChangeTexture) {
			currentTime = 0.0f;

			indexTexture++;
			if (indexTexture >= textures.size())
				indexTexture = 0;
		}

		Texture texture{ textures[indexTexture] };

		glm::mat4 model{ 1.0f };
		model = glm::translate(model, glm::vec3{ position, 0.0f });
		model = glm::rotate(model, glm::radians(rotate), glm::vec3{ 0.0f, 0.0f, 1.0f });
		model = glm::translate(model, glm::vec3{ size * -0.5f, 0.0f });
		model = glm::scale(model, glm::vec3{ size, 1.0f });

		shader.use();
		shader.setMat4("model", model);
		shader.setVec3("spriteColor", color);
		texture.bind();

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}
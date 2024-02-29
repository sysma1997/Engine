#include "../../Include/2D/Rectangle.h"

namespace E2D {
	Rectangle::Rectangle() : 
		Object{ Shader{ "Shaders/2D/Rectangle.vert", "Shaders/2D/Rectangle.frag" } } {}

	void Rectangle::draw() {
		glm::mat4 model{ 1.0f };
		model = glm::translate(model, glm::vec3{ position, 0.0f });
		model = glm::rotate(model, glm::radians(rotate), glm::vec3{ 0.0f, 0.0f, 1.0f });
		model = glm::translate(model, glm::vec3{ size * -0.5f, 0.0f });
		model = glm::scale(model, glm::vec3{ size, 1.0f });

		shader.use();
		shader.setMat4("model", model);
		shader.setVec3("color", color);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}
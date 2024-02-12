#include <Engine.h>
#include <Shader.h>

int main() {
	Engine* engine{ new Engine{"Test"} };
	engine->setKeyCallback([](GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_ESCAPE && GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
	});

    float vertices[] = {
        0.5f, -0.5f, 0.0f,  // right down
        -0.5f, -0.5f, 0.0f, // left down
        0.0f, 0.5f, 0.0f,   // up
    };

    Shader* shader{ new Shader{"Shaders/triangle/triangle.vert", "Shaders/triangle/triangle.frag"} };

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    float color[] = {
        1.0f, 1.0f, 1.0f, // RGB
    };

    while (engine->isLoop()) {
        engine->newFrame();

        shader->use();
        shader->setVec3("color", glm::vec3{ 1.0f });

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        engine->renderFrame();
	}

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader->id);

    glfwTerminate();
	return 0;
}
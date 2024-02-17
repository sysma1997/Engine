#pragma once

#include <map>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Shader.h"
#include "../Texture.h"

namespace EUI {
    struct Character {
        GLuint id;
        glm::ivec2 size;
        glm::ivec2 bearing;
        unsigned int advance;
    };

    class Label
    {
    private:
        GLuint VAO, VBO;

    public:
        std::map<char, Character> characters;
        Shader shader;
        
        Label(std::string font, int fontSize, float width, float height);
        
        void loadFont(std::string font, int fontSize);
        void render(std::string text, glm::vec2 position, 
            float scale = 1.0f, glm::vec3 color = glm::vec3{1.0f});
        glm::vec2 getSizeText(std::string text, float scale = 1.0f);
    };
}
#include "Shader.h"

Shader::Shader() {}
Shader::Shader(std::string vertexPath, std::string fragmentPath) {
	std::string log{ "SHADER::" };
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	std::stringstream sstr;

	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertexPath, std::ios::in);
	if (!vertexShaderStream.is_open()) {
		std::cout << LOG << log << "Failed to open " << vertexPath << ". Are you in the right directory? Don't "
			<< "forget to read the FAQ!\n";
		return;
	}
	sstr << vertexShaderStream.rdbuf();
	vertexShaderCode = sstr.str();
	vertexShaderStream.close();
	sstr.str("");

	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragmentPath, std::ios::in);
	if (!fragmentShaderStream.is_open()) {
		std::cout << LOG << log << "Failed to open " << fragmentPath << ". Are you in the right directory? Don't "
			<< "forget to read de FAQ!\n";
		return;
	}
	sstr << fragmentShaderStream.rdbuf();
	fragmentShaderCode = sstr.str();
	fragmentShaderStream.close();
	
	GLint success;
	char infoLog[512];

	// COMPILING VERTEX SHADER
	char const* vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
	glCompileShader(vertexShaderID);
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
		std::cout << LOG << log << "Error to compile vertex shader: " << infoLog << '\n';
	}

	// COMPILING FRAGMENT SHADER
	char const* fragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
	glCompileShader(fragmentShaderID);
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
		std::cout << LOG << log << "Error to compile fragment shader: " << infoLog << '\n';
	}

	// LINK PROGRAM
	id = glCreateProgram();
	glAttachShader(id, vertexShaderID);
	glAttachShader(id, fragmentShaderID);
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << LOG << log << "Error to linking shaders with program: " << infoLog << '\n';
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}
Shader::~Shader() {}

void Shader::use() {
	glUseProgram(id);
}

void Shader::setBool(const std::string& name, bool value, bool useShader) {
	if (useShader) use();
	glUniform1i(glGetUniformLocation(id, name.c_str()), static_cast<int>(value));
}
void Shader::setInt(const std::string& name, int value, bool useShader) {
	if (useShader) use();
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value, bool useShader) {
	if (useShader) use();
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, glm::vec2 value, bool useShader) {
	if (useShader) use();
	glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
}
void Shader::setVec3(const std::string& name, glm::vec3 value, bool useShader) {
	if (useShader) use();
	glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
}
void Shader::setVec4(const std::string& name, glm::vec4 value, bool useShader) {
	if (useShader) use();
	glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
}
void Shader::setMat4(const std::string& name, glm::mat4 value, bool useShader) {
	if (useShader) use();
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
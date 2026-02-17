#include "Shader.h"

#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
	std::string vertexSource = loadShaderSource(vertexPath);
	std::string fragmentSource = loadShaderSource(fragmentPath);

	const char* vs = vertexSource.c_str();
	const char* fs = fragmentSource.c_str();

	unsigned int vertexShader, fragmentShader;

	int success;
	char infoLog[512];

	// Vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vs, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Vertex Shader Compilation Failed:\n" << infoLog << std::endl;
	}

	// Fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fs, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Fragment Shader Compilation Failed:\n" << infoLog << std::endl;
	}

	// Shader program
	shaderPID = glCreateProgram();
	glAttachShader(shaderPID, vertexShader);
	glAttachShader(shaderPID, fragmentShader);
	glLinkProgram(shaderPID);

	glGetProgramiv(shaderPID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderPID, 512, NULL, infoLog);
		std::cout << "Shader Program Linking Failed:\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader() {
	glDeleteProgram(shaderPID);
}

void Shader::bind() const {
	glUseProgram(shaderPID);
}

void Shader::unbind() const {
	glUseProgram(0);
}

void Shader::setUniform(const std::string& name, float value) const {
	glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform(const std::string& name, const glm::vec2& value) const {
	glUniform2f(getUniformLocation(name), value.x, value.y);
}

void Shader::setUniform(const std::string& name, const glm::vec3& value) const {
	glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
}

void Shader::setUniform(const std::string& name, const glm::vec4& value) const {
	glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::setUniform(const std::string& name, const glm::mat4& value) const {
	// must pass glm::value_ptr to get the raw float array from the matrix.
	// if we just pass &value, it will give us the address of the glm::mat4 object not the float array.
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

std::string Shader::loadShaderSource(const std::string& filePath) const {
	std::ifstream file(filePath);
	std::string source;
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			source += line + "\n";
		}
		file.close();
	} else {
		std::cout << "Failed to open shader file: " << filePath << std::endl;
	}

	return source;
}

/*
* Calling glGetUniformLocation is NOT a free operation.
* The lookup can be expensive, so cache the uniform locations in a map to avoid redundant lookups.
*/
int Shader::getUniformLocation(const std::string& name) const {
	if (uniformLocationCache.find(name) != uniformLocationCache.end())
		return uniformLocationCache[name];

	int location = glGetUniformLocation(shaderPID, name.c_str());
	uniformLocationCache[name] = location;
	return location;
}

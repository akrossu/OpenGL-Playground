#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader {
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();
	
	void bind() const;
	void unbind() const;

	void setUniform(const std::string& name, float value) const;
	void setUniform(const std::string& name, const glm::vec2& value) const;
	void setUniform(const std::string& name, const glm::vec3& value) const;
	void setUniform(const std::string& name, const glm::vec4& value) const;
	void setUniform(const std::string& name, const glm::mat4& value) const;

	unsigned int getShaderPID() const { return shaderPID; }
private:
	unsigned int shaderPID;
	mutable std::unordered_map<std::string, int> uniformLocationCache;

	std::string loadShaderSource(const std::string& filePath) const;
	int getUniformLocation(const std::string& name) const;
};
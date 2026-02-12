#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer {
public:
    void init(int width, int height);
    void render();
private:
    unsigned int shaderProgram;
    unsigned int VAO, VBO, EBO;
	int widthRef, heightRef;

    void setupShaders();
    void setupBuffers();
};
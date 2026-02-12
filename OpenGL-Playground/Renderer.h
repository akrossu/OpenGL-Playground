#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer {
public:
    void init();
    void render();
private:
    unsigned int shaderProgram;
    unsigned int VAO, VBO, EBO;

    void setupShaders();
    void setupBuffers();
};
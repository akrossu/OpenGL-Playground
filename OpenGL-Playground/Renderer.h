#pragma once

#include <glad/glad.h>

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
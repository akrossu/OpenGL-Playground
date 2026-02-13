#pragma once


#include "Texture.h"

class Renderer {
public:
    void init(int width, int height);
    void render();
private:
    unsigned int shaderProgram;
    unsigned int VAO, VBO, EBO;
	int widthRef, heightRef;

    Texture* texture = nullptr;

    void setupShaders();
    void setupBuffers();
};
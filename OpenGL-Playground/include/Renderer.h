#pragma once

#include "Texture.h"
#include "Shader.h"

struct Objects {
    Shader* shader;
    Texture* texture;
    glm::mat4 model;
};

class Renderer {
public:
    void init(int width, int height);
    void render();
private:
    std::vector<Objects> objects;
    unsigned int VAO, VBO, EBO;
	int widthRef, heightRef;

    void setupBuffers();
};
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.h"

void Renderer::init(int width, int height) {
	widthRef = width;
	heightRef = height;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); // default

    glClearColor(0.129f, 0.157f, 0.188f, 1.0f);

    setupBuffers();

    Texture* texture1 = new Texture("assets/textures/texture1.jpg", false);
    Texture* texture2 = new Texture("assets/textures/texture2.jpg", false);

    Shader* shader1 = new Shader("assets/shaders/vertex1.glsl", "assets/shaders/fragment1.glsl");
    Shader* shader2 = new Shader("assets/shaders/vertex2.glsl", "assets/shaders/fragment2.glsl");

    Objects obj1 = {
        shader1,
        texture1,
        glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f))
    };

    Objects obj2 = {
        shader2,
        texture2,
        glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f))
	};

    objects.push_back(obj1);
	objects.push_back(obj2);
}

void Renderer::setupBuffers() {
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    unsigned int indices[] = { 0, 1, 3, 1, 2, 3 };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Renderer::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(VAO);

	float time = static_cast<float>(glfwGetTime());

	// Create transformations
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)widthRef / (float)heightRef, 0.1f, 100.0f);
	model = glm::rotate(model, time * glm::radians(45.0f), glm::vec3(0.25f, 0.25f, 0.5f));

    for (auto& obj : objects) {
        obj.shader->bind();

        glm::mat4 model = glm::rotate(obj.model, time * glm::radians(45.0f), glm::vec3(0.25f, 0.25f, 0.5f));
        
		obj.shader->setUniform("model", model);
        obj.shader->setUniform("view", view);
        obj.shader->setUniform("proj", proj);

		obj.shader->setUniform("u_resolution", glm::vec2(widthRef, heightRef));
		obj.shader->setUniform("u_time", time);

        if (obj.texture) {
            obj.texture->bind(0);
			obj.shader->setUniform("u_Texture", 0);
        }

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

	glBindVertexArray(0);
}
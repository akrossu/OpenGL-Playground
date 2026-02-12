#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"
#include "Renderer.h"
#include "Platform.h"

static Renderer renderer;

Application::Application(int width, int height) {
	initWindow(width, height);
	initOpenGL();
}

Application::~Application() {
	glfwTerminate();
}

void Application::initWindow(int width, int height) {
	/* Initialize the library */
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		exit(-1);
	}

	/* Set window hints before creating the window */
	WindowHints hints;
#ifdef __APPLE__
	hints.forwardCompatible = true; // MacOS compat
#endif // __APPLE__

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Makes an initial call. Then for every window size update creates a callback */
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void Application::initOpenGL() {
	/* Initialize GLAD before any OpenGL functino calls */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}
	renderer.init();
}

/* Called when the window size changes.
* (0, 0) is the bottom-left corner of the window
* (width, height) sets the opengl viewport to the size of the window
*/
void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void Application::run() {
	while (!glfwWindowShouldClose(window)) {
		renderer.render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
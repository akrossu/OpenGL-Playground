#pragma once

struct GLFWwindow;

class Application {
public:
	Application(int width, int height);
	~Application();
	void run();

private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	void initWindow(int width, int height);
	void initOpenGL();

	GLFWwindow* window = nullptr;
	int width;
	int height;
};